#include <utility>
#include <ctime>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <set>
#include <unordered_map>
#include <boost/serialization/unordered_map.hpp>
#include "database.h"
extern "C" {
#include "hiredis.h"
}


namespace intersect {
    template <class Key, class Value>
    class RedisValueDatabase : public ValueDatabase<Key,Value>{
        public:
            RedisValueDatabase(int database=0){
                m_context = redisConnect("127.0.0.1", 6379);
                //std::cout << database << std::endl << std::flush;
                redisReply *reply = (redisReply*) redisCommand(m_context, "SELECT %d", database);
                freeReplyObject(reply);
            }

            virtual Value get(Key key){
                std::ostringstream oss;
                boost::archive::text_oarchive oa(oss);
                oa << key;
                std::string sKey = oss.str();
                redisReply *reply = (redisReply*) redisCommand(m_context, "GET %b", sKey.c_str(), sKey.length());
                Value value;
                if (reply->type == REDIS_REPLY_STRING){
                    std::string replyValue = std::string(reply->str, reply->len);
                    std::istringstream iss(replyValue);
                    boost::archive::text_iarchive ia(iss);
                    ia >> value;
                }
                freeReplyObject(reply);
                return value;
            }
            virtual void put(Key key, Value value){
                std::ostringstream oss1;
                boost::archive::text_oarchive oa1(oss1);
                oa1 << key;
                std::string sKey = oss1.str();
                std::ostringstream oss2;
                boost::archive::text_oarchive oa2(oss2);
                oa2 << value;
                std::string sValue = oss2.str();
                redisReply *reply = (redisReply*) redisCommand(m_context, "SET %b %b", sKey.c_str(), sKey.length(), sValue.c_str(), sValue.length());
                freeReplyObject(reply);
            }
            virtual void remove(Key key){
                std::ostringstream oss;
                boost::archive::text_oarchive oa(oss);
                oa << key;
                std::string sKey = oss.str();
                redisReply *reply = (redisReply*) redisCommand(m_context, "DEL %b", sKey.c_str(), sKey.length());
                freeReplyObject(reply);
            }
            virtual int size() {
                redisReply *reply = (redisReply*) redisCommand(m_context, "DBSIZE");
                return (int)reply->integer;

            }

        protected:
            redisContext *m_context;
    };

} // end namespace intersect

