CAAAW: The bird password manager
================================
.. image:: https://img.shields.io/badge/Build%20(fedora)-passing-2a7fd5?logo=fedora&logoColor=2a7fd5&style=for-the-badge
   :alt: Build = Passing
   :target: https://github.com/ElisStaaf/CAAAW
.. image:: https://img.shields.io/badge/Version-1.0.0-38c747?style=for-the-badge
   :alt: Version = 1.0.0
   :target: https://github.com/ElisStaaf/CAAAW
.. image:: https://img.shields.io/badge/Language-C++-grey?logo=c%2B%2B&logoColor=white&labelColor=blue&&style=for-the-badge
   :alt: Language = C++
   :target: https://github.com/ElisStaaf/CAAAW

CAAAW is a password manager that acts like a bird; sometimes really amazing and majestic, and sometimes a
gremlin that steals all of your shiny objects. If a memory leak happens, you're not allowed to sue me, I
made this project for learning purposes, after all. It supports saving passwords into files, passwords
with different categories, passwords for different websites and specific logins for the aforementioned
websites. It's overall a pretty useful tool, but don't expect a GUI here, no! Developers with brains know
that all real and productive work happens in the terminal. So yeah, terminal based password manager in C++.

Requirements
------------
* `gcc`_ (or any other C++ compiler)
* `make`_
* `cmake`_
* `git`_ or `gh`_

Installation
------------
To install, firstly clone the repo:

.. code:: sh

   # git
   git clone https://github.com/ElisStaaf/CAAAW caw

   # gh
   gh repo clone ElisStaaf/CAAAW caw

After cd-ing into the ``caw`` directory, you would want to build
an executable using ``cmake``:

.. code:: sh

   cmake .
   sudo make

.. _`gcc`: https://gcc.gnu.org/install
.. _`make`: https://www.gnu.org/software/make
.. _`cmake`: https://cmake.org/download
.. _`git`: https://git-scm.com/downloads 
.. _`gh`: https://github.com/cli/cli#installation
