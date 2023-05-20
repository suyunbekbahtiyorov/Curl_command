# Welcome to My Curl
***

## Task
Welcome to My Curl

## Description
HTTP Protocol is used everywhere and pretty easy to read, this project will lead you to its world.

You will create a my_curl command (very similar to the UNIX command curl)
my_curl is a tool to get data from a server, using HTTP. The command is designed to work without user interaction.

How does it work?
You send an url as parameter and it will print the html content of a web page.

my_curl only supports HTTP.

$>./my_curl http://www.columbia.edu/~fdc/sample.html
<!DOCTYPE HTML>
<html lang="en">
<head>
...
<p>
<i>(End)</i>

<hr>
</body>  <!-- close the <body> begun above -->
</html>  <!-- close the <html> begun above -->
How would you be able to do this magic?
Using sockets. They are file descriptors.

Navigation world wide web and diagram | Client, Server, Create Socket, Create Socket, Bind socket to port, Socket socket to port, Connect, Listen, Send the connect request to server and waiting server to respond, Client traffic is up here and wait to be accepted Client accepted be ready for send and receive data between server, Accept, Process inside the bracket will happen when request of client is accepted. Send and, Send and receive data, sendto / recyfrom, receive data, close

## Installation
make

## Usage

```
make
./my_curl https://od315e2ac-51c5.docode.fi.qwasar.io/#/home/docode/project
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
