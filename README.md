<div id="top"></div>

# CSE340 Redux
The CSE 340 Summer Project to see if I can improve upon my code and the instructor's provided code. The goal of this is to create more robust and professional code rather than code that is just passable. The instructor provided code supported only taking input from `std::cin`. This greatly frustrated debugging efforts in IDE based environments, and inspired me to remake this project.
Note: This code is written in C++11. C++11 was a requirement because the current automatic grading system was not set up for c++14 or c++17.
Note: This code is not the solution for any of the assignments, it is merely a alternative to the instructor provided code
### Goals: 
- Add ability to optionally read from file stream instead of only `std::cin`
- Minimize number of source files to be updated as keywords change for each assignment
- Apply modern c++11 techniques as referenced by the c++ Core Guidelines to both design and implementation
  - Use c++ namespaces
  - RAII using `std::unique_ptr` instead of `new` and `delete`
  - Use NVI where applicable
  - Use exceptions and `try/catch()` instead of `exit()`
  - Practice good `const` variable and method habits

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
