sh scripts/build.sh release 

rm -rf -d collisions

mkdir collisions

cp bin/release/collisions collisions
cp -r res collisions

echo "Deploy build created."
echo "cd collisions to find it"