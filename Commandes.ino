void manageCommande(char input[40], int lenght) {
  char chiffreToSet[] = "    ";
  char commande[] = "   ";
  for (int i = 0; i < 3; i++)
  {
    commande[i] = input[i];
  }

  if (strcmp(commande, cSetDistanceTrain)  == 0) {
    if (lenght > 3) {
      for (int i = 3; i < lenght; i++) {
        chiffreToSet[i - 3] = input[i];
      }
      setDistanceTrain(chiffreToSet);
    }
    else
      setDistanceTrainSenseur();
  }
  if (strcmp(commande, cGetDistanceTrain)  == 0)
    getDistanceTrain();
  if (strcmp(commande, cGetDistance)  == 0)
    getDistance();
  if (strcmp(commande, cGetRunningTime)  == 0)
    getRunningTime();
  if (strcmp(commande, cStartDMX)  == 0)
    startDMX();
  if (strcmp(commande, cActiverSenseur)  == 0)
    activerSenseur();
  if (strcmp(commande, cDesactiverSenseur)  == 0)
    desactiverSenseur();
  if (strcmp(commande, cGetSenseur)  == 0)
    getSenseurState();
  if (strcmp(commande, cGetAll)  == 0)
    getAll();
  if (strcmp(commande, cTempsTrain)  == 0) {
    if (lenght > 3) {
      for (int i = 3; i < lenght; i++) {
        chiffreToSet[i - 3] = input[i];
      }
      setTempsTrain(chiffreToSet);
    }
  }
    if (strcmp(commande, cTempsDMX)  == 0) {
    if (lenght > 3) {
      for (int i = 3; i < lenght; i++) {
        chiffreToSet[i - 3] = input[i];
      }
      setTempsDMX(chiffreToSet);
    }
  }
  if (strcmp(commande, cSetRange)  == 0) {
    if (lenght > 3) {
      for (int i = 3; i < lenght; i++) {
        chiffreToSet[i - 3] = input[i];
      }
      setRange(chiffreToSet);
    }
  }
}

void startDMX() {
  if (dmxON == false) {
    DmxSimple.write(1, 255);
    dmxON = true;
    tempsDepuisStartDMX = millis();
  }
}

void getDistanceTrain() {
  xbeeSend(String(distanceTrain) + '\n' + '\n', r2Addr);
}

void getRunningTime() {
  xbeeSend(String(millis() / 1000) + '\n', r2Addr);
}

void getDistance() {
  xbeeSend(String(distance) + '\n', r2Addr);
}


void setDistanceTrain(char chiffreToSet[]) {
  distanceTrain = atoi(chiffreToSet);
  EEPROM.write(0, highByte(distanceTrain));
  EEPROM.write(1, lowByte(distanceTrain));
  xbeeSend(String(distanceTrain) + '\n', r2Addr);
}

void setDistanceTrainSenseur() {
  distanceTrain = distance;
  EEPROM.write(0, highByte(distanceTrain));
  EEPROM.write(1, lowByte(distanceTrain));
  xbeeSend(String(distanceTrain) + '\n', r2Addr);
}

void setTempsDMX(char tempsToSet[]) {
  tempsDMX = atoi(tempsToSet);
  EEPROM.write(2, tempsDMX);
  xbeeSend(String(tempsDMX) + '\n', r2Addr);
}

void setTempsTrain(char tempsToSet[]) {
  tempsTrain = atoi(tempsToSet);
  EEPROM.write(3, tempsTrain);
  xbeeSend(String(tempsTrain) + '\n', r2Addr);
}

void setRange(char rangeToSet[]) {
  range = atoi(rangeToSet);
  EEPROM.write(4, range);
  xbeeSend(String(range) + '\n', r2Addr);
}

void activerSenseur() {
  senseur = true;
}

void desactiverSenseur() {
  senseur = false;
}

void getAll() {
  String all = "gt" + String(distanceTrain) + "gd" + String(distance) + "gr" + String(millis() / 1000) + "gtt" + String(tempsTrain) + "gtd" + String(tempsDMX) + "gra" + String(range);
  if (senseur == true)
    all += "as" + String(senseur);
  else
    all += "as" + String(senseur);
  Serial.println(all);
  xbeeSend(all + '\n', r2Addr);
}

void getSenseurState() {
  xbeeSend(String(senseur) + '\n', r2Addr);
}














