hello-cbase
===========

a hello world program using chromiums base library


hello-cbase uses the same build tools as Chromium, so you'll need to set up the build environment as described in the [Chromium instructions](http://www.chromium.org/developers).

Once this is done, you can fetch the sources by doing:

>`mkdir hello-cbase`  
>`cd hello-cbase`  
>`gclient config https://github.com/wesedens/hello-cbase.git --name=src`  
>`gclient sync`  

hello-cbase is built with ninja. Once you have the source code you can generate the ninja files by running the following command.

>`cd src`  
>`gn gen out/Debug`  

TODO:
I haven't figured out how to generate a release build or run `gn` from `gclient` yet because `gclient` runs actions in a python subprocess with the cwd above src and you can't change directories within the child process.
