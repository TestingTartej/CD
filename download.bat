@echo off
setlocal

:: Get the directory where the batch file is located
set "SCRIPT_DIR=%~dp0"
set "FOLDER_NAME=Compiler Design"
set "ZIP_FILE=%SCRIPT_DIR%compiler_design.zip"
set "TARGET_FOLDER=%SCRIPT_DIR%%FOLDER_NAME%"

:: Google Drive file ID (Extracted from your provided link)
set "FILE_ID=1ZZp28WYoJWV-tL69GPaVKsZzQJSgPu-E"
set "DOWNLOAD_URL=https://drive.google.com/uc?export=download&id=%FILE_ID%"

:: Check if the folder exists
if not exist "%TARGET_FOLDER%" mkdir "%TARGET_FOLDER%"

:: Download the ZIP file using PowerShell
echo Downloading files...
powershell -Command "(New-Object System.Net.WebClient).DownloadFile('%DOWNLOAD_URL%', '%ZIP_FILE%')"

:: Check if the ZIP file was downloaded
if exist "%ZIP_FILE%" (
    echo Extracting files...
    powershell -Command "Expand-Archive -Path '%ZIP_FILE%' -DestinationPath '%TARGET_FOLDER%' -Force"
    echo Extraction complete.
    del "%ZIP_FILE%"  :: Delete ZIP after extraction
) else (
    echo Download failed. Check the URL.
)

echo Done!
pause