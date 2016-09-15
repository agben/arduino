/*
 * 8x8 led array testing - see led_testing.fzz
 * Display an eye that looks left/right and then blinks - using bitmaps of images
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int col[] = {14,10,4,12,9,5,8,6};    //columns - driven LOW for on
int row[] = {11,7,3,15,2,13,16,17};  //rows - driven HIGH for on

// bitmaps of images to display
byte ledBitmap[5][8] = {
  B00101000,              //open
  B10111010,
  B01000100,
  B10010010,
  B01000100,
  B00111000,
  B00000000,
  B00000000,

  B00101000,              //left
  B10111010,
  B01000100,
  B10100010,
  B01000100,
  B00111000,
  B00000000,
  B00000000,

  B00101000,              //right
  B10111010,
  B01000100,
  B10001010,
  B01000100,
  B00111000,
  B00000000,
  B00000000,

  B00101000,              //half open
  B10010010,
  B01101100,
  B11010110,
  B01101100,
  B00010000,
  B00000000,
  B00000000,

  B00101000,              //closed
  B10101010,
  B01111100,
  B11111110,
  B01111100,
  B00000000,
  B00000000,
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
  ledout(0,0,0,30);            // Open eye centre
  ledout(1,0,0,30);            // Open eye left
  ledout(0,0,0,30);            // Open eye centre
  ledout(2,0,0,30);            // Open eye right
  ledout(0,0,0,30);            // Open eye centre
  ledout(3,0,0,3);             // half-open
  ledout(4,0,0,6);             // closed
  ledout(3,0,0,3);             // half-open

/*
  for (int i=0; i<10; i++) ledout(0,0,0);
  for (int i=0; i<5; i++) ledout(1,0,0);
  for (int i=0; i<10; i++) ledout(0,0,0);
  for (int i=0; i<5; i++) ledout(2,0,0);
  for (int i=0; i<10; i++) ledout(0,0,0);
  ledout(3,0,0);
  for (int i=0; i<3; i++) ledout(4,0,0);
  ledout(3,0,0);
/*
  for (int i=0; i<10; i++)                //scroll 0-9 from right to left
  {
    for (int j=8; j>-7; j--) ledout(i,j,0);
  }

  for (int i=9; i>=0; i--)                //scroll 9-0 from bottom to top
  {
    for (int j=-6; j<9; j++) ledout(i,0,j);
  }

  for (int i=0; i<10; i++)                //scroll 0-9 from top to bottom
  {
    for (int j=8; j>-7; j--) ledout(i,0,j);
  }

  for (int i=9; i>=0; i--)                //scroll 9-0 from bottom left to top right
  {
    for (int j=-6; j<9; j++) ledout(i,j,j);
  }

  for (int i=0; i<10; i++)                //scroll 0-9 from bottom right to top left
  {
    for (int j=8; j>-7; j--) ledout(i,j,-j);
  }

  for (int i=1; i<10; i++)                //flash a +x+x pattern before starting again
  {
    ledout(10,0,0);
    ledout(11,0,0);
  }
*/
}

void ledout(int iBitMapNo, int hOffset, int vOffset, int iDuration)            //offset bitmap display
{
  for (int i=0; i<iDuration; i++)        //repeat image a few times to ensure the eye can see it
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

