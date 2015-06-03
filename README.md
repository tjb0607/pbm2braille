# pbm2braille
Renders a raw PBM image to text using Unicode Braille symbols

there's literally no comments in my code lmao

##compiling

    gcc -std=c11 ./pbm2braille.c -o pbm2braille

##usage

it'll accept a raw PBM image and render it as text. Just give the PBM file as the first argument, or pipe it in.

    $ ./pbm2braille ./image.pbm
    ⠀⠀⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⣿⠞⠻⣷⠀⣿⠀⣰⠟⠻⣦⠀⣰⠞⠛⢷⡀
    ⣿⠀⠀⣿⠀⣿⠀⣿⠀⠀⣀⠀⣿⠛⠛⠛⠃
    ⠿⠀⠀⠿⠀⠿⠀⠘⠷⠾⠋⠀⠘⠷⠶⠟⠁
    $ cat ./image.pbm | ./pbm2braille
    ⠀⠀⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⣿⠞⠻⣷⠀⣿⠀⣰⠟⠻⣦⠀⣰⠞⠛⢷⡀
    ⣿⠀⠀⣿⠀⣿⠀⣿⠀⠀⣀⠀⣿⠛⠛⠛⠃
    ⠿⠀⠀⠿⠀⠿⠀⠘⠷⠾⠋⠀⠘⠷⠶⠟⠁
    $

GIMP, imagemagick, etc. can export as PBM.
