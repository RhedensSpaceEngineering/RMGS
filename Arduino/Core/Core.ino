void setup() {
  /////////////////
  // Beeldscherm //
  /////////////////
  beeldscherm();
}

void loop() {
  beeldscherm_BootStart();
  delay(4000);
  beeldscherm_Draw("Loading...", 0);
  delay(5000);
  beeldscherm_BootFinished();
  delay(4000);
}
