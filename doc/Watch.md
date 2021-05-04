# watch

Found a nice tool that calls a program with static output over and avoer again. E.g. a programm that prints out a sensor reading for exaample is called every 0.3 seconds by callinh:
```bash
watch -n0.3 printSensorData
```
This is nice, but the really nice thing is:
* assume you have a large monitor, or a second one
* a open terminal window that is connected to a raspberry pi with some sensors attached
* vscode with a remote workspace attached to the raspberry pi
* you write a program that reads/displays data from the sensor

Thanks to watch you have 'instant' feedback ... I mean compiling still needs some time. But for small programs, prototypes are a more apt description, it is nice. Especially if you want to test your code and writing tests is just too cumbersome for trial and error stuff that interacts with the real world.

Sure, once you have verified that your prototype works you start writing unit tests and integration tests and fuzzers and stuff like that. At least to me it is easier to work on that if I know the technical stuf somehow works. I would never use it for production. The costs are way to high, first to marked can get its boner from somewhere else.
