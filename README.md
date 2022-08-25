<div id="top"></div>

<p align="center">
    <!--
    <a href="https://github.com/mnfitz-ASU/cse340redux/pulse" alt="Activity">
        <img src="https://img.shields.io/github/commit-activity/mnfitz-ASU/cse340redux" /></a>
    <a href="https://discord.gg/sKXHzHpq">
        <img src="https://img.shields.io/discord/308323056592486420?logo=discord"
            alt="chat on Discord"></a>
    -->
    <a href="https://github.com/mnfitz-ASU/mnfitz-ASU/graphs/contributors" alt="Contributors">
        <img src="https://img.shields.io/github/contributors/mnfitz-ASU/mnfitz-ASU" /></a>    
    <a href="https://www.linkedin.com/in/matthew-n-fitzgerald/">
        <img src="https://img.shields.io/badge/-matthewf-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/matthew-n-fitzgerald/"
            alt="follow on Linkedin"></a>
</p>


# CSE340 Redux
The CSE 340 Senior Year Summer Project to improve upon my knowledge of C++ and the instructor's provided code. This project improves upon the instructor provided CSE 340 "skeleton code" used as the basis for all CSE 340 programming assignments. This project was inspired by th edifficulty I had trying to debug CSE 340 assignments in an IDE. Because the skeleton code only took input from `std::cin`, this frustrated efforts to do source level debugging from wthin an IDE.
My goal is to modify this skeleton code so that it could integrate with an IDE based debugger 
<br/>
Note: This code is entirely in C++11, as it's a requirement by the current automatic grading system. 
<br/>
Note: This code is not the solution for any of the assignments, it is merely a alternative to the instructor provided code

## Goals: 
#### 1.0: Allow all editing and debugging to take place in [VSCode](https://code.visualstudio.com/).
```
// Same editing/debugging experience for Mac, Windows, and Linux
```
#### 2.0: Allow VSCode to optionally take input from file instead of exclusively 'std::cin' 
```
# Old Method: input from std::cin
$ ./a.out < ./test/testfile.txt # always std::cin

# New Method: optional commandline arg for inputfile
$ ./a.out ./test/testfile.txt # argv[argc-1]
```
#### 3.0: Minimize number of source files to be updated as keywords change for each assignment
```
# Added new token.h and token.cc source files that 
# contain the keywords for any specific assignment 
# Assignment specific versions of these files live 
# in their own subdirectory ./projectN
# This means the makefile must select the source
# file from the appropriate subdirectory

$ pwd
/c/Users/mn-fi/Projects/git/cse340redux
$ ls project*
project1:
token.cc  token.h

project2:
token.cc  token.h

project3:
token.cc  token.h

project4:
token.cc  token.h
```
#### 4.0: Use key/value dictionary to store assignment specific set of keywords
```
/// Prefer std::unordered_map over std::map as we don't need any sorted order of keys
using KeywordDict = std::unordered_map<std::string, TokenKind>;
```
#### 5.0: Use modern OO techniques and [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) where possible for both design and implementation
```
// Use c++ namespaces
// Use [NVI](https://en.wikipedia.org/wiki/Non-virtual_interface_pattern) for base/derived class interface
// Use `throw` instead of `exit()` for program exceptions
// Practice good `const` variable and method habits
```
### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```
  
<!-- LICENSE -->
### License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
