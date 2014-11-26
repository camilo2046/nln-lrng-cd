* CS1 Compilers: CS1 Compilers MOOC Sample Code

Installation Steps
    https://class.stanford.edu/courses/Engineering/Compilers/Fall2014/6b750292e90d4950b895f621a5671b49/
    - Install packages (If you only intend to use the C++ version, you don't need the jdk). 
      For Ubuntu: sudo apt-get install flex bison build-essential csh openjdk-6-jdk libxaw7-dev
    - Make the /usr/class directory:
      sudo mkdir /usr/class
    - Make the directory owned by you:
      sudo chown $USER /usr/class
    - Go to /usr/class and download the tarball:
      cd /usr/class
      wget http://spark-university.s3.amazonaws.com/stanford-compilers/vm/student-dist.tar.gz
    -Untar:
      tar -xf student-dist.tar.gz
    -If you want things exactly like the VM:
      Add a symlink to your home directory:
      ln -s /usr/class/cs143/cool ~/cool
    - Add the bin directory to your $PATH environment variable. If you are using bash, add to your .profile (or .bash_profile, etc. depending on your configuration; note that in Ubuntu have to log out and back in for this to take effect):
      PATH=/usr/class/cs143/cool/bin:$PATH
      