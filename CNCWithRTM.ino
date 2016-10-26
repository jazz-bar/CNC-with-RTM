
volatile int i;
volatile float input_line[4][6]; 
void setup() {
cli();
TCCR1A = 0;
TCCR1B = 0;
TCNT1 = 0;
OCR1A = 15600;
TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);
TCCR1B |= (1<<WGM12);
TIMSK1 |= (1<<OCIE1A);
sei();
Serial.begin(9600);
delay(200);
  char line[ LINE_BUFFER_LENGTH ];
  char c;
  int lineIndex;
  bool lineIsComment, lineSemiColon;
Serial.println("New_LINE");
  lineIndex = 0;
  lineSemiColon = false;
  lineIsComment = false;
}

void loop() {
while ( Serial.available() > 0 ) {

      c = Serial.read();
      if (( c == '\n') || (c == '\r') ) {             // End of line reached
        if ( lineIndex > 0 ) {                        // Line is complete. Then execute!
          line[ lineIndex ] = '\0';                   // Terminate string
          if (verbose) {
            Serial.print( "Received : ");
            Serial.println( line );
          }
//          processIncomingLine( line, lineIndex );

          lineIndex = 0;
        }
        else {
          // Empty or comment line. Skip block.
        }
        lineIsComment = false;
        lineSemiColon = false;
        Serial.println("ok");

      }
      else {
        if ( (lineIsComment) || (lineSemiColon) ) {   // Throw away all comment characters
          if ( c == ')' )  lineIsComment = false;     // End of comment. Resume line.
        }
        else {
          if ( c <= ' ' ) {                           // Throw away whitepace and control characters
          }
          else if ( c == '/' ) {                    // Block delete not supported. Ignore character.
          }
          else if ( c == '(' ) {                    // Enable comments flag and ignore all characters until ')' or EOL.
            lineIsComment = true;
          }
          else if ( c == ';' ) {
            lineSemiColon = true;
          }
          else if ( lineIndex >= LINE_BUFFER_LENGTH - 1 ) {
            Serial.println( "ERROR - lineBuffer overflow" );
            lineIsComment = false;
            lineSemiColon = false;
          }
          else if ( c >= 'a' && c <= 'z' ) {        // Upcase lowercase
            line[ lineIndex++ ] = c - 'a' + 'A';
          }
          else {
            line[ lineIndex++ ] = c;
          }
        }
      }
//    }
}
ISR(TIMER1_COMPA_vect){
  Serial.println('0x13');
  i++;
  Serial.println(i);
  Serial.println('0x11');
  
}



  


