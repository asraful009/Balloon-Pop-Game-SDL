#!/bin/bash

set -e

GAME=PopDrop
BUILD_DIR=build/bin
OUT_DIR=PopDrop-itch
LIB_DIR=$OUT_DIR/lib

echo "🧹 Cleaning old package..."
rm -rf $OUT_DIR
mkdir -p $LIB_DIR

echo "📦 Copying executable..."
cp $BUILD_DIR/$GAME $OUT_DIR/

echo "🔍 Finding dependencies..."

# Get SDL2 + related libs only
ldd $BUILD_DIR/$GAME | grep "SDL2\|image\|mixer\|ttf" | awk '{print $3}' | grep "/" | while read lib; do
    echo "  -> $lib"
    cp $lib $LIB_DIR/
done

echo "🚀 Creating run script..."
cat > $OUT_DIR/run.sh << 'EOF'
#!/bin/bash
DIR="$(dirname "$0")"
LD_LIBRARY_PATH="$DIR/lib" "$DIR/PopDrop"
EOF

chmod +x $OUT_DIR/run.sh

echo "📝 Copy README..."
cp README.txt $OUT_DIR/ 2>/dev/null || true

echo "🗜️ Creating zip..."
cd $OUT_DIR/..
zip -r PopDrop-Linux-x86_64.zip PopDrop-itch

echo "✅ DONE!"
echo "📦 Output: PopDrop-Linux-x86_64.zip"