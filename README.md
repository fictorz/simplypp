# SilkRoad

## Installation
- Install Ubuntu from microsoft store
- Install VSCode on your local machine.

### Docker installation
- Open Ubuntu
- Access the repository from the Linux machine using /mnt/c/[...] where /c is the C: drive in windows
- Install Make using: sudo apt install make
- Follow the 'Install using the apt repository' from https://docs.docker.com/engine/install/ubuntu/ 

## Testing
- Run : sudo make test

### Known bug
If the docker.sh script fails, it may be caused by CRLF line endings in files.
- Install dos 2unix using: sudo apt-get install dos2unix
- Run if error occurs while doing make test, run these commands in Ubuntu:
    dos2unix ./docker.sh
    dos2unix .env

### Adding a test
- Add a source file in '/test/**'
- Add the file path into /test/CMakeList.txt

### Running specific test
`export GTEST_FILTER="TestControlEngine*"; ./manage.sh ce`

