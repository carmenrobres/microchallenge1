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

![WhatsApp Image 2024-02-16 at 15 23 46](https://github.com/carmenrobres/microchallenge1/assets/147055292/a4e11169-6cd3-4bba-9c9c-1b9525b4bd9e)


#### Iteration 1
![ITeration 1](https://github.com/carmenrobres/microchallenge1/assets/145042059/52a172f3-bdde-4a2e-be31-88d34c86e9b0)

#### Playing with Heartbeat sensor


https://github.com/carmenrobres/microchallenge1/assets/145042059/b36eaae2-ec2b-4257-b77c-70317b949014
https://github.com/carmenrobres/microchallenge1/assets/145042059/81c04e57-5235-4150-973f-f9a7f36aa8db

#### Iteration 2
![ITeration 2](https://github.com/carmenrobres/microchallenge1/assets/145042059/c4e8d823-ab0d-4ca1-86e1-60300913ad60)
![Diagram](https://github.com/carmenrobres/microchallenge1/assets/145042059/6f3defc2-8137-4491-a591-ea3631245b1b)

### Code

Code for vibration motor

Code for wifi

Code together

### Fabrication process
For the pendant, we looked for a 3D model of a container that could be opened through a screwing mechanism to integrate the electronics seamlessly. We downloaded a model from Thingyverse and scaled it to a bigger size to be able to fit the electronics. We also added holes on both sides of the model to be able to plug in the LED light, the vibration motor, the chain and the capacitive wires.

The 3D printing took several iterations, as the first models did not have enough adherence to the bed and failed. We therefore added a raft to the model for better adherence, and the ensuing prints were successful.

https://github.com/carmenrobres/microchallenge1/assets/147055292/076de704-3b1a-47f5-b084-2b780e98fe50


### Build of Materials

Iteration 1: Barduino, BreadBoard, Vibration motor
Iteration 2: Esp 32 Xiao, Vibration motor, LED, Battery, Resistance
Casing
Cable sensor


### Documents and files
### References

## Final Conclusions
We had big ambitions about this necklace during the ideation phase, but this was a humbling experience as we realised that developing what seem to be simple technology can be very cumbersome, especially in a short amount of time. We therefore scaled down on ambition. 

### Photo
### Reflect about future development opportunity
Instead of integrating a breathing exercise of 5 breaths, we could integrate a sensor that would detect when the user is more relaxed, which would stop the breathing exercise. 
We would also like to gather the data collected about anxiety to make a visual installation of the level of anxiety in a certain location, if several users are wearing the necklace.
We also thought of linking an AI that would send you a notification when you are fidgeting asking you why you were anxious, to encourage journalling and help people reflect on their anxiety.

### Described problems and how the team solved them

Coding

3D printing:
![WhatsApp Image 2024-02-16 at 15 23 46](https://github.com/carmenrobres/microchallenge1/assets/147055292/79599299-4fdb-41a4-b8ab-37b9962e98d4)
