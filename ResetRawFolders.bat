@echo off
echo "Emptying raw folders..."
cd rawFolders/raw20MIN
del *.txt
cd ../rawBBC
del *.txt
cd ../rawDIARIO
del *.txt
cd ../rawCNN
del *.txt
cd ../rawNYT
del *.txt
cd ../../
echo "Done"
pause