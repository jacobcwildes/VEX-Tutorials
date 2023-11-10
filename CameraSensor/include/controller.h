struct ConDat
{
  int desiredPos;
  int turn;
  int forw;
  int left;
  int right;
  int back;
  int debugDrive;
  int divisor = 1;
};

int controllerUse(ConDat *controllerData);