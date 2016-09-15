/*
 * 8x8 led array testing - see led_testing.fzz
 * Matrix countdown with sliding display - using bitmaps of images
 * i.e. how to scroll messages in any direction
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int col[] = {14,10,4,12,9,5,8,6};    //columns - driven LOW for on
int row[] = {11,7,3,15,2,13,16,17};  //rows - driven HIGH for on

// bitmaps of images to display
byte ledBitmap[12][8] = {
  B00111100,              //0
  B01000010,
  B01100010,
  B01010010,
  B01001010,
  B01000110,
  B01000010,
  B00111100,

  B00000100,              //1
  B00001100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00001110,

  B00111100,              //2
  B01000010,
  B01000010,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B01111110,

  B00111110,              //3
  B00000100,
  B00001000,
  B00011100,
  B00000010,
  B00000010,
  B00000010,
  B00111100,

  B00001100,              //4
  B00010100,
  B00100100,
  B01000100,
  B01111110,
  B00000100,
  B00000100,
  B00000100,

  B00111110,              //5
  B01000000,
  B01000000,
  B00111100,
  B00000010,
  B00000010,
  B01000010,
  B00111100,

  B00000100,              //6
  B00001000,
  B00010000,
  B00111100,
  B01000010,
  B01000010,
  B01000010,
  B00111100,

  B00111110,              //7
  B00000010,
  B00000100,
  B00001000,
  B00111100,
  B00010000,
  B00100000,
  B01000000,

  B00111100,              //8
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B01000010,
  B01000010,
  B00111100,

  B00111100,              //9
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B00001000,
  B00010000,
  B00100000,

  B10000001,              //X
  B11000011,
  B01100110,
  B00011000,
  B00011000,
  B01100110,
  B11000011,
  B10000001,
  
  B00011000,              //+
  B00011000,
  B00011000,
  B11111111,
  B11111111,
  B00011000,
  B00011000,
  B00011000,

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
  for (int i=0; i<10; i++)                //flash numbers 0-9
  {
    for (int j=0; j<4; j++) ledout(i,0,0);  //display each several times to hold the image on the matrix
  }

  for (int i=9; i>=0; i--)                //scroll 9-0 from left to right
  {
    for (int j=-6; j<9; j++) ledout(i,j,0);
  }

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

