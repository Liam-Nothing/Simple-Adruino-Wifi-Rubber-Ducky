<p align="center">
    <img src="README_SRC/main_img.png" width="200">
</p>

# Simple wifi bad usb pro-micro & wemos d1 mini

- ## Description :

	A simple wifi bad usb with pro-micro & wemos d1 mini. The program is designed to send a payload to a computer when it is connected to the computer. The program uses the arduino ide and the arduino pro-micro and wemos d1 mini card.

- ## Requirements :
  
  - Pro-micro
  - Wemos d1 mini

- ## How to use :

  - Upload the code to cards
  - Connect the pro-micro to the computer
  - Connect devices to the wemos d1 mini wifi
    - SSID : `Wifi-Bad-USB`
    - Password : `123456789`
  - Send payload to the computer using the button

- ## Customization :

  - Add new payload :
	- Create a new function for wemos d1 mini
    	- `server.on("/payload2", handlePayload2);`
			```
			void handlePayload2() {
				digitalWrite(additionalPins[0], HIGH);
				digitalWrite(additionalPins[1], LOW);
				digitalWrite(additionalPins[2], HIGH);
				digitalWrite(additionalPins[3], HIGH);
				digitalWrite(additionalPins[4], HIGH);
				
				Serial.println("PAYLOAD1");
				String html = "<html><head>";
				html += "<meta http-equiv='refresh' content='2;url=/'></head>";
				html += "<body><h1>Waiting...</h1></body></html>";
				server.send(200, "text/html", html);
				delay(200);
				for (int i = 0; i < numAdditionalPins; i++) {
					digitalWrite(additionalPins[i], LOW);
				}
			}
			```
	- Add new button for wemos d1 mini
		- `html += "<br/><p><a href=\"/payload2\">Send payload2 (1 0 1 1 1)</a></p>";`
	- Create a new function for pro-micro