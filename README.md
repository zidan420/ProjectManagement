# Project Management
**Version**: 1.0


## Defaults
A default account, with the following credential, is always created:
```
corposer:Corpos3r
```
:warning: Do **NOT** store any sensitive data on default account as the credential is public


## Installation
#### IN WINDOWS
1. Download the zip file (https://github.com/zidan420/ProjectManagement/archive/refs/heads/main.zip)
2. Extract the zip file
3. Open the folder where the zip is extracted
4. Either,
    + compile it using a compiler in cmd.exe:
```
gcc project_management.c -o project_management
```
4. Or,
    + Create a new ```empty project``` (in codeblocks or VS)
    + Add the ```c file```, the ```database folder``` and the ```header file```
    + Compile and run it

#### IN LINUX
1. ```git clone https://github.com/zidan420/ProjectManagement.git```
2. ```cd ProjectManagement```
3. ```gcc project_management.c -o project_management```

## Features
+ Uses encryption similar to ```brainfuck```
+ Provides ```Sign Up```/```Login``` facility
+ Uses mechanism to prevent ```Buffer overflow```
+ **Purpose**:
    + For ```adding```, ```editing````, ```listing``` and ```removing``` projects
    + ```Storing``` Projects in Database
    + Each user gets ```1 database```


## Compatibility

>1. Windows 10 or newer
>2. Linux
