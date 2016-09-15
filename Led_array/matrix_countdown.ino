/*
 * 8x8 led array testing - see led_testing.fzz
 * Matrix countdown display - using bitmaps of images
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
//int row[] = {14,10,4,12,9,5,8,6};    //rows - driven LOW for on
//int col[] = {17,16,13,2,15,3,7,11};  //columns - driven HIGH for on
int row[] = {14,10,4,12,9,5,8,6};    //rows - driven LOW for on
int col[] = {11,7,3,15,2,13,16,17};  //columns - driven HIGH for on

// bitmaps of images to display
byte ledBitmap[11][8] = {
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

  B00111100,              //9
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B00001000,
  B00010000,
  B00100000,

  B00111100,              //8
  B01000010,
  B01000010,
  B01000010,
  B00111100,
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

  B00000100,              //6
  B00001000,
  B00010000,
  B00111100,
  B01000010,
  B01000010,
  B01000010,
  B00111100,

  B00111110,              //5
  B01000000,
  B01000000,
  B00111100,
  B00000010,
  B00000010,
  B01000010,
  B00111100,

  B00001100,              //4
  B00010100,
  B00100100,
  B01000100,
  B01111110,
  B00000100,
  B00000100,
  B00000100,

  B00111110,              //3
  B00000100,
  B00001000,
  B00011100,
  B00000010,
  B00000010,
  B00000010,
  B00111100,

  B00111100,              //2
  B01000010,
  B01000010,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B01111110,

  B00000100,              //1
  B00001100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00000100,
  B00001110,
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
  for (int k=2; k<11; k++)		// display images 2 to 11 (9 to 1)
  {
    for (int j=0; j<20; j++)	// repeat the image display to make it appear static
    {							// (persistence of vision)
      ledout(k);
    }
  }

  for (int k=1; k<5; k++)		// toggle between the X and + icons at the end of the countdown
  {
    for (int j=0; j<8; j++)
    {
      ledout(0);
    }
    for (int j=0; j<8; j++)
    {
      ledout(1);
    }
  }
}

void ledout(int i)                    //light requested bitmap
{
  for (int j=0; j<8; j++)             //for each column
  {
    for (int k=0; k<8; k++)           //turn off all rows
    {
      digitalWrite(row[k], HIGH);
    }

    for (int k=0; k<8; k++)           //turn off all columns except current column
    {
      if (k==j)
      {
        digitalWrite(col[k], HIGH);
      }
      else
      {
        digitalWrite(col[k], LOW);
      }
    }

    for (int k=0; k<8; k++)            //turn on required leds in current row
    {
      if (bitRead(ledBitmap[i][j],k))
      {
        digitalWrite(row[k], LOW);
      }
    }
    delay(3);
  }
}



