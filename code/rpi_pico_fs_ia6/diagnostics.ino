void diagnostics(int i){
  Serial.print("Channel");
  Serial.print(i);
  Serial.print(":");
  Serial.print(joystickValues[i]);
  Serial.print(",");
}