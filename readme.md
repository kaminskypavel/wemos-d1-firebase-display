# wemos-d1-firebase-display

## Installation

### Arduino IDE
* download [firebase-arduino](https://github.com/googlesamples/firebase-arduino/archive/master.zip)
* Arduino Studio > Sketch > Include Library > Add .ZIP Library

### Firebase
* create new project
* navigate to `https://console.firebase.google.com/u/0/project/<Project Name>/settings/general/`
* copy "Database secrets" from `https://console.firebase.google.com/u/0/project/<Project Name>/settings/serviceaccounts/databasesecrets`
(Database secrets are currently deprecated and use a legacy Firebase token generator. Update your source code with the Firebase Admin SDK.)

* make sure your firebase rules are set to 
```javascript
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```

### Gotchas
* if you're getting 
  * `Firebase.h:26:25: fatal error: ArduinoJson.h: No such file or directory`" 
  * `FirebaseObject.h:109:21: error: 'StaticJsonBuffer' was not declared in this scope`   
* Arduino Studio > Sketch > Include Library > **make sure ArduinoJson is version 5.13.2**


