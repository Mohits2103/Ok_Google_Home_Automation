# Ok_Google_Home_Automation

Control any home appliances using Google assistant in your mobile

# Steps 

1 - Create a Adafruit.io account

2 - In your Dashboards section Select Actions->Create new dashboard

3 - Give a name and desciption

4 - Open new dashboard and find *Create new block* or '+' symbol, and choose 'Toggle' option

5 - At 'Enter new feed name' enter "Relay1" and create, similarly create "Relay2", "Relay3", "Relay4" feeds also.

6 - Now select "Relay1" and 'Next step', Here replace "On" with "1" and "Off" with "0" respectively, do this for all relays.

7 - Find the AIO userID and key in your dashboard (It will be in key symbol).

8 - Now Create a account in IFTTT website (Using the same mail ID you gave for Adafruit.io account)

9 - Create New Applet

10 - It should show "If +This then +That".

11 - Click on "+This" and select google assistant

12 - Type "Room Light On" and select what response you need and create.

13 - Now click on "+That" and select adafruit.

14 - Select your account->Dasboard->Relay1 and enter the value '1' for On (Similarly '0' for Off) and create.

15 - Repeat steps 9 to 14 for all the 4 relays and all conditions (On and Off).

16 - Do basic relay connections to the devices and you are now ready.
