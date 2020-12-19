<h1> ESP8266 IOT Stock Ticker / Message board </h1>

<p align="center">
  <img width="100%" src="https://media3.giphy.com/media/PZd40vBSo7y2EyLOUI/giphy.gif" />
</p>

<h3> This project wasn't just a stock ticker. </h3><h4>I learned so much regarding electronics, programming, firmware, and soldering.<br> Engineering.</h4>

![Simplified schematic](https://i.imgur.com/kvImfjr.png)
<h4> Extremely simplified schematic, describes outputs of shift register to 7-Segment display </h4>

<h3> Simplified process: </h3>
<ol type="1">
  <li> Request quote provider from site with HTTPS GET request
  <li> Convert JSON data into usable data, retrieve prices + percentages
  <li> Convert characters to binary data (8 bit) for GPIO
  <li> Use 3 GPIO pins to send data to 74HC595 (Shift register)
  <li> Give power to specified 7 segment display
  <li> Repeat 4-5 until stock refresh 
</ol>  


![before](https://i.imgur.com/yApSDmy.png)
![b4](https://i.imgur.com/YFTRrGq.png)
<h4> Breadboard, not connected to internet </h4>

![without](https://i.imgur.com/akoQNLu.jpg)
![b1](https://i.imgur.com/bfad5Ob.jpg)
![t1](https://i.imgur.com/eHElAEL.jpg)
<h4> Investing in a soldering iron and a somewhat usable station, I ended up with this insanely complex PCB prototype. </h4>
<h3> It can display any message from any website quick and easily, and it only needs an internet connection </h3>
<h4> Project time: 4-5 months. This includes:</h4>
<ul>
<li> Learning how to build circuits from scratch. </li>
<li> IV Curves, Parallel circuits, etc: The laws of electronics. (Asking questions on forums) </li> 
<li> Testing (and breaking) ESP8266-01s
<li> Creating code for multiplexing 7-Segment LEDs
<li> Hours of headaches trying to upload code 
<li> Setting up stock-retrieving systems, JSON -> Usable data
<li> Learning protocols for HTTPS on outdated systems that do not support it. 
<li> Designing general circuit from new electronic knowledge, learning while creating 
<li> Converting breadboard (temporary) build to a prototype PCB (more permanant)
<li> Learning to solder, soldering extremely tight wires and layers. 
<li> Undoing wires to find broken / faulty connections
</ul>

<h3> Overall, this project isn't a stock ticker. It's a gateway to doing so many more projects with IOT, electronics, soldering, and projects that are impactful. </h3>
