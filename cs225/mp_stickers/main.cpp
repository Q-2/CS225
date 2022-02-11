#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image frog; frog.readFromFile("human.png");
  Image keyboard; keyboard.readFromFile("keyboard.png");
  Image MP; MP.readFromFile("MP.png");
  Image error; error.readFromFile("error.png");
  StickerSheet frogpix(frog,5);
  MP.scale(.5);
  keyboard.scale(.2);
  error.scale(.5);
  frogpix.addSticker(keyboard, 300, 300);
  frogpix.addSticker(error, 150, 50);
  frogpix.addSticker(MP,0,0);
  Image output;
  output = frogpix.render();
  output.writeToFile("frogmeme.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
