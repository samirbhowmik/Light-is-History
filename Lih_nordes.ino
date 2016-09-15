
/*light is history*/
/******************************************************/
//max target is 10
// to here one puts values, that the light will reach in two hour time.
// for now, it contains timing adjustment test values.

//60 very bright
//40 bright
//20 dim
//5 very dim

int light_target[20]={
  2, 25, 60, 2, 25, 2, 60, 2, 15, 25, 2, 60, 2, 60, 2, 25, 25, 25, 25, 25};

/******************************************************/
// this sets the maximum time, calibrated to within minutes.
int MAXHOURS=150;//150
int MAXSECONDS=29;//29
int MAXADJUST=155;//1555
/******************************************************/
// do not touch these
int seconds=0;
int direc=0;
int twohours=0;
int adjust=0;
int iComp=0;
int lightpin[20]={
  22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41};
/******************************************************/
int light[20];
/******************************************************/
void setup()
{
  //  Serial.begin(9600);
  for( int i =0;i<20;i++)
  {
    pinMode(lightpin[i],OUTPUT);
    digitalWrite(lightpin[i],LOW);
  }
  zero_values();
  update_targets();
}
/******************************************************/
void das_licht()
{
  iComp++;

  if( iComp > 60)
  {
    iComp=0;
  }

  for(int meh=0;meh<20;meh++)
  {
    if( light[meh]==0 )
    {
      digitalWrite(lightpin[meh],LOW);
    }
    else if( light[meh]>=60 )
    {
      digitalWrite(lightpin[meh],HIGH);
    }
    else if( iComp>= light[meh] )
    {
      digitalWrite(lightpin[meh],LOW);
    }
    else
    {
      digitalWrite(lightpin[meh],HIGH);
    }
  }
}
/******************************************************/
void zero_values()
{
  for(int muu=0;muu<20;muu++)
  {
    light[muu]=0;
  }
}
/******************************************************/
void update_targets()
{
  for(int foo=0;foo<20;foo++)
  {
    if( direc==0)
    {

      light[foo]=((MAXHOURS*60-twohours*(60-light_target[foo])))/(MAXHOURS-1);
    }
    else
    {
      light[foo]=( MAXHOURS*(light_target[foo]) + ((60-light_target[foo]) * twohours) )/(MAXHOURS-1);
    }
  }
}
/******************************************************/
void loop()
{
  if( adjust < MAXADJUST )
  {
    adjust++;
  }
  else
  {
    adjust=0;
    if(seconds < MAXSECONDS )
    {
      seconds++;
    }
    else
    {
      if( twohours < MAXHOURS )
      {
        twohours++;
      }
      else
      {
        twohours=0;
        zero_values();
        if( direc==1)
        {
          direc=0;
        }
        else
        {
          direc=1;
        }
      }
      update_targets();
      seconds=0;
    }
  }
  das_licht();
}
/******************************************************/
/******************************************************/


