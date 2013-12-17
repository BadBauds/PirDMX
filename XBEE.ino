void readXBee() {                                                 //process incoming traffic from the XBee
  byte delyStatus, discStatus;

  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {    //is this an rx packet
      xbee.getResponse().getZBRxResponse(rx);               //yes, get the received data
      Serial.println("XBee unexpected RX");                 //this sensor unit is send-only, so we do not actually expect to receive data

      for (int i=0; i<rx.getDataLength(); i++) {
        Serial.print((char)rx.getData(i));
      }
      
            char commande[rx.getDataLength()+1];
      for (int i=0; i<rx.getDataLength(); i++) {
        commande[i] = (char)rx.getData(i);
      }
      manageCommande(commande,rx.getDataLength());
      Serial.println();
    } 

    else if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {    //transmit status for packets we've sent
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      //get the delivery status, the fifth byte
      delyStatus = txStatus.getDeliveryStatus();
      discStatus = txStatus.getDiscoveryStatus();
      if (delyStatus == SUCCESS) {
       Serial.println("XBee TX OK");
      }
      else {  //the remote XBee did not receive our packet. is it powered on and configured correctly?
        Serial.println("XBee TX ERROR");
      }
    }

    else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {    //XBee administrative messages
      xbee.getResponse().getModemStatusResponse(msr);
      if (msr.getStatus() == ASSOCIATED) {
        Serial.println("XBee associated");
      } 
      else if (msr.getStatus() == DISASSOCIATED) {
        Serial.println("XBee disassociated");
      } 
      else {
        Serial.println("XBee other status");        //some other status
      }
    }

    else {
      Serial.println("XBee unexpected input");        //something else we were not expecting
    }
  }
}

void xbeeSend(String data, XBeeAddress64 destAddr) {
  buildPayload(data);        //build the XBee payload
  xbeeTX(destAddr, strlen(&xbeePayload[0].C));     //send it
}

void xbeeTX(XBeeAddress64 destAddr, int payloadSize ) {

  //build the tx request
  zbTx.setAddress64(destAddr);
  zbTx.setAddress16(0xFFFE);
  zbTx.setPayload(&xbeePayload[0].B);
  zbTx.setPayloadLength(payloadSize);
  xbee.send(zbTx);
}

void buildPayload(String input){
  xbeePayload[0].C = '#';
  for (int i=0; i<=(input.length()+1); i++) {
    xbeePayload[i+1].C = input.charAt(i);
  }
}







