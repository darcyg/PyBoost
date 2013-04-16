
cd hiredis
make

cd ..
cd vlfeat-0.9.16
make

cd ..
cd boost_1_52_0
./bootstrap.sh --with-libraries=serialization,program_options
./b2

echo "Done installing thirdparty dependencies"

