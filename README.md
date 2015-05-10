# pbm2braille
Renders a PBM image to text using Unicode Braille symbols

there's literally no comments in my code lmao

##compiling

    gcc -std=c11 ~/programming/pbm2braille/pbm2braille.c -o pbm2braille

##usage

it'll accept a PBM image and render it as text. Just give the PBM file as the first argument, or pipe it in.

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
