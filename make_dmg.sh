#!/bin/sh

TMP_DIR="/tmp/flurry-build/"
PLIST=`pwd`/Info
VERS=`defaults read $PLIST CFBundleShortVersionString`
DMG_NAME="Flurry.$VERS.dmg"

mkdir -p $TMP_DIR/flurry
xcodebuild -target Flurry -configuration Release SYMROOT=$TMP_DIR

cp -r $TMP_DIR/Release/Flurry.saver /tmp/flurry-build/flurry
cp -r readme.rtfd $TMP_DIR/flurry
find $TMP_DIR -name .DS_Store -delete

hdiutil create ~/Desktop/$DMG_NAME -ov -srcfolder $TMP_DIR/flurry -volname Flurry 

rm -r $TMP_DIR
