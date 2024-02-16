# microchallenge1

## Initial Idea
### Interests
We were both interested in the impact of technology on emotions and mental health as well as making imperceptible things perceptible, using technology to help us understand ourselves and others. In a world where anxiety and depression is on the rise, we therefore thought of ways to sense and visualise anxiety through technology to help us and others address this uncomfortable feeling.
### Concept
We decided to create a wearable device that would sense your anxiety and help you follow breathing exercises guided by vibrations to calm down. As anxiety is often an irrational feeling, it is hard to communicate to others. What is more, most people are not even consicous of the fact that they are anxious. This is why we decided to make this device collaborative: when it senses that you're anxious, the device sends a signal to a paired device (a partner, a friend etc.), which helps them understand how you're feeling and act accordingly, without needing any communication from your side.
### References
### Planning
![image](https://github.com/carmenrobres/microchallenge1/assets/145042059/e4d4272d-3707-42e0-b500-31bdad4e0203)

### Integrated Design 
Sensing anxiety with technology through anatomical parameters is challenging, as sensors, such as heartbeat sensors, are hard to calibrate. We therefore had to find a proxy indicator to sense anxiety. We decided to use fidgeting, as we often express anxiety through unconscious mimics. Fidgeting would be detected through a capacitive sensor which would detect when skin is touching the wearable. Having observed that we often play with our rings when we are anxious, our first idea was to create a ring, but we later realised that the electronics to operate the systems would take too much space to be integrated in a ring, so we decided to create a necklace instead.

The necklace consist of a pendant where all electronics would be integrated. To interact with the user, the pendant has a vibration motor on one side to guide the breathing exercise, a capacitive wire on the surface to detect touch when the user is fidgeting, and a LED light on the other side to signal when the user's partner is fidgeting. We first wanted to have the vibration in the neck, but opening the necklace to wear it would not have been possible with the soldered wires. We therefore decided to put the entire electronic mechanism in the pendant. 

## Process
### Electronics

#### Iteration 1
![ITeration 1](https://github.com/carmenrobres/microchallenge1/assets/145042059/52a172f3-bdde-4a2e-be31-88d34c86e9b0)

#### Playing with Heartbeat sensor


https://github.com/carmenrobres/microchallenge1/assets/145042059/b36eaae2-ec2b-4257-b77c-70317b949014
https://github.com/carmenrobres/microchallenge1/assets/145042059/81c04e57-5235-4150-973f-f9a7f36aa8db

#### Iteration 2

![ITeration 2 (1)](https://github.com/carmenrobres/microchallenge1/assets/145042059/b8a68586-0f7e-45b8-8094-b3b721644305)

![Diagram (1)](https://github.com/carmenrobres/microchallenge1/assets/145042059/945f7ad1-847c-4cf7-a443-52fc0cc5b395)


### Code

Code for vibration motor
![MOTOR_CODE](https://github.com/carmenrobres/microchallenge1/assets/145042059/e9527346-c5eb-4178-a97d-9507a5110c37)

Code for wifi
![WIFI_CODE](https://github.com/carmenrobres/microchallenge1/assets/145042059/d961ff6f-c2b7-4504-a207-ec870e60c32d)

Code together
![CODE](https://github.com/carmenrobres/microchallenge1/assets/145042059/3b1b0a4c-38b0-4758-bf15-1d8a3d4c4214)

### Fabrication process
For the pendant, we looked for a 3D model of a container that could be opened through a screwing mechanism to integrate the electronics seamlessly. We downloaded a model from Thingyverse and scaled it to a bigger size to be able to fit the electronics. We also added holes on both sides of the model to be able to plug in the LED light, the vibration motor, the chain and the capacitive wires.

The 3D printing took several iterations, as the first models did not have enough adherence to the bed and failed. We therefore added a raft to the model for better adherence, and the ensuing prints were successful.

### Build of Materials

Iteration 1: Barduino, BreadBoard, Vibration motor
Iteration 2: Esp 32 Xiao, Vibration motor, Flora Neopixel, Battery 3.3V, Casing
Cable sensor


### Documents and files
### References

## Final Conclusions
We had big ambitions about this necklace during the ideation phase, but this was a humbling experience as we realised that developing what seem to be simple technology can be very cumbersome, especially in a short amount of time. We therefore scaled down on ambition. 

### Photo
![FInal idea](https://github.com/carmenrobres/microchallenge1/assets/145042059/fce539fc-656c-4bfc-a830-deaddc43f828)

### Reflect about future development opportunity
Instead of integrating a breathing exercise of 5 breaths, we could integrate a sensor that would detect when the user is more relaxed, which would stop the breathing exercise. 
We would also like to gather the data collected about anxiety to make a visual installation of the level of anxiety in a certain location, if several users are wearing the necklace.
We also thought of linking an AI that would send you a notification when you are fidgeting asking you why you were anxious, to encourage journalling and help people reflect on their anxiety.

### Described problems and how the team solved them

Coding+electronics:
- Delays!
- Xiao didn't work with touch sensor
- Broke the battery :(

3D printing:
- Add holes to connect the cables
- Add raft for better adherence to the bed

![WhatsApp Image 2024-02-16 at 15 23 46](https://github.com/carmenrobres/microchallenge1/assets/147055292/f63e65be-2cac-4446-8eec-4bb442080773)

