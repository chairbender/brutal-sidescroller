/*
This program takes a midi file and turns it into a brutal platformer map file.

It converts any tempo changes into brutal platformer tempo changes, and any other midi events it encounters
into enemies. So, if a user wants to make a level, they just load the song up in something and match midi notes to where
they want enemies (screams) to be.
*/
#include <stdio.h>
#include <MidiFileIn.h>

int main(int argc, char *argv[]) {
	//Get the file from the command line arguments
	if (argc != 2) {
		std::cout << "please specify the midi file to parse and the destination file";
		return -1;
	}

	//Load the midi file using the stk midiin
}
