/*
 * 8x8 led array testing - see led_testing.fzz
 * Cycle through a simple set of pacman bitmap images to open and close his mouth.
 *   At the same time slide the images around the 8x8 matrix to provide movement 
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int col[] = {14,10,4,12,9,5,8,6};    //columns - driven LOW for on
int row[] = {11,7,3,15,2,13,16,17};  //rows - driven HIGH for on

// bitmaps of images to display
byte ledBitmap[3][8] = {
  B00000000,              //nearly closed
  B00111100,
  B01111110,
  B01111110,
  B01111100,
  B01111110,
  B00111100,
  B00000000,

  B00000000,              //half open
  B00111100,
  B01111110,
  B01111000,
  B01110000,
  B01111110,
  B00111100,
  B00000000,

  B00000000,              //full open
  B00111100,
  B01111000,
  B01110000,
  B01100000,
  B01111110,
  B00111100,
  B00000000,

};

void setup()
{
  for (int i=0; i<8; i++)        //set arduino pins to be outputs
  {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
}

void loop()
{
  for (int j=-6; j<9; j++)
  {
    if (j%2)
    {
      for (int i=0; i<3; i++) ledout(i,j,0);
    }
    else
    {
      for (int i=2; i>=0; i--) ledout(i,j,0);
    }
  }
}

void ledout(int iBitMapNo, int hOffset, int vOffset)            //offset bitmap display
{
  for (int i=0; i<4; i++)                //repeat image a few times to ensure the eye can see it
  {
    for (int j=0; j<8; j++)              //for each row
    {
      if (j+vOffset>=0 && j+vOffset<8)   //within the boundaries of the chosen bitmap
      {
        for (int k=0; k<8; k++)          //set leds in current row according to the bitmap
        {
          digitalWrite(col[k], !bitRead(ledBitmap[iBitMapNo][j+vOffset],k+hOffset));
        }
        digitalWrite(row[j], HIGH);      //display the row, lighting required leds
      }
      delay(2);                          //pause for it to be seen
      digitalWrite(row[j], LOW);         //turn row off again
    }
  }
}

