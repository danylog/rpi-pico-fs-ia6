<h2>
A simple option to connect a FLYSKY controller to any PC or Mac for flight simulators.
</h2>
<p>
This project uses RPI Pico's native HID support, which avoids the use of virtual contollers and allows to use it with a Mac, something that I couldn't find on any forum before.

For now, only works with PWM (tested with FS-IA6)

Apart from the controller and the receiver, you'll need jumper cables, a Rapberry Pi Pico and a USB cable to connect it to your computer. Even the cheapest RP240 board for $2 from Aliexpress will do fine.
</p>

<b>Instructions:</b>
<ol>
  <li>Connect the Pico and the receiver like in the image (jumper cables work also):
  <img width="820" alt="image" src="https://github.com/user-attachments/assets/14a9b0cd-6908-4765-8e00-24662e367523" />
    </li>
  <li>(if not done before) Bind the receiver and the controller. On how to do it, watch <a href="https://www.google.com/search?q=fs-ia6+binding&sca_esv=c1daa74f5b79c9cd&rlz=1C5CHFA_enES1060ES1060&udm=2&biw=1680&bih=962&sxsrf=AHTn8zpQ3h7FtCNBa6pQPiV8gF4jig6Kqw%3A1743081200241&ei=8E7lZ8S0Due6i-gPkuy7oQU&ved=0ahUKEwjE7IS-q6qMAxVn3QIHHRL2LlQQ4dUDCBE&uact=5&oq=fs-ia6+binding&gs_lp=EgNpbWciDmZzLWlhNiBiaW5kaW5nMgUQABiABDIGEAAYBRgeSPwTUMgBWNcScAJ4AJABAJgBUKABqAWqAQE5uAEDyAEA-AEBmAIKoAKMBcICBxAjGCcYyQLCAgYQABgHGB7CAgoQABiABBhDGIoFwgIEEAAYHsICBhAAGAgYHpgDAIgGAZIHAjEwoAfIErIHATi4B_oE&sclient=img#vhid=ZXcVvIt5zVw37M&vssid=mosaic">this video</a>.</li>
  <li>Hold the on-board button on the Pico and connect it to a USB port. It should appear as a removable drive. You can release the button.</li>
  <li>Drag and drop the .ul2 file downloaded from the <a href="https://github.com/danylog/rpi-pico-fs-ia6/releases">releases page</a> to that drive. The drive should disappear.</li>  
  <li>That's it! Now the pico should be recognized as a gamepad by your computer. It is recommended to calibrate it in your sim since the axis and buttons can be different for any controller.</li>
</ol>

<p>
  If you wish to collaborate or just rebuild the Pico firmware for your own needs, you can use the .ino files and Arduino IDE. <a href="https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/">Instructions on how to use Arduino IDE for RPI Pico</a>
</p>
