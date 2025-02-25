

** Carplay:

Bonjour is a networking technology developed by Apple that enables devices to discover each other and communicate on a local network without any configuration. It is based on the Zeroconf (Zero Configuration Networking) protocol, which allows devices to automatically find services like printers, file shares, and other computers on the network without needing a central server or manual IP address setup.
DNS-SD (DNS Service Discovery): Bonjour uses DNS-SD to advertise and discover services. Devices broadcast information about available services using multicast DNS (mDNS), which allows other devices on the network to discover and connect to them by name rather than IP address.
Multicast DNS (mDNS): Bonjour relies on mDNS, a protocol that resolves hostnames to IP addresses within small networks that don't have a local DNS server. This allows devices to find each other using human-readable names like printer.local or macbook.local.

** CP via Wifi:

1.Setup for CarPlay over wireless begins with Bluetooth discovery between the device and the accessory.
2.The user initiates pairing on the accessory either through a long press on the accessoryʼs Siri button, or by using the accessoryʼs
user interface. On the device the user initiates pairing via the iOS Settings app. The accessory and the device may
choose to show all detected Bluetooth devices, or they may choose to show only devices that support CarPlay over
wireless by querying the Bluetooth Extended Inquiry Response (EIR). A Bluetooth Classic pairing flow generates a
record of trust between the device and the accessory.
In addition, the pairing process can be simplified by just plugging in the device over USB and executing Out-Of-Band
Bluetooth Pairing as described in Accessory Interface Specification.
During initial pairing, the accessory provides the Wi-Fi access pointʼs Wi-Fi credentials (SSID and Passphrase) using
iAP2 over Bluetooth
These Wi-Fi credentials are stored on the
device and will be used to join the Wi-Fi access point automatically during reconnection. To speed up the reconnection
scenario, the device will initiate Wi-Fi scanning based on a re-connect of any Bluetooth profile.
After starting iAP2, accessories using 5 GHz Wi-Fi access points for CarPlay may negotiate all of the relevant Bluetooth
profiles such as HFP, A2DP, AVRCP, etc.
3.After Bluetooth pairing is completed, the accessory connects iAP2 over Bluetooth and declares support for CarPlay
over wireless. 
4.Once the device confirms that CarPlay over wireless is available, the accessory request a session initiation
and provides the Wi-Fi credentials and the IP address to be used for the connection.
5.The device will join the accessoryʼs access point and establish a CarPlay session

** IAP2:
iAP2 provides a standardized method for accessories to interact with iOS devices. It allows for seamless communication between an iPhoneand an accessory, managing things like media control, app data sharing, and even CarPlay functionalities.
iAP2 allows the accessory (such as a car’s head unit) to control the iOS device, providing access to media libraries, call handling, and navigation control through the car’s interface.
iAP2 is integral to Apple CarPlay, enabling iOS devices to connect to car infotainment systems. It helps manage communication, allowing CarPlay to mirror the iPhone’s interface onto the car’s display, control apps, and transfer navigation, media, and call data seamlessly.
When you connect your iPhone to a CarPlay-enabled car (via USB or wirelessly), the iPhone and the car’s infotainment system communicate using iAP2.

** Audio Streaming:
The accessory must support audio input and output streams encoded as follows:
• CarPlay over USB
– LPCM.
– Raw AAC-LC for high latency audio (main buffered audio).
• CarPlay over wireless
– Raw AAC-LC for high latency audio (main high audio and main buffered audio).
– OPUS for low latency audio (alternate audio, auxiliary audio and main audio except ”media”).

Pulse Audio is used for streaming Audio
H264 for Video

In broad terms ALSA is a kernel subsystem that provides the sound hardware driver, and PulseAudio is the interface engine between applications and ALSA


