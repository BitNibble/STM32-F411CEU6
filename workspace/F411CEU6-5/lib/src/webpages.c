#include "webpages.h"

const char* htmlContent_1 =
		"<!DOCTYPE html>"
		"<html lang='en'>"
		"<head>"
		"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
		"<title>ESP8266 Example</title><style>body { font-family: Arial, sans-serif; } h1 { color: #333; }</style>"
		"</head>"
		"<body>"
		"<h1>Sergio Welcome to ESP8266 PHP Page!</h1><p>This is a simple HTML page served by PHP.</p>"
		"</body>"
		"</html>";
const size_t htmlContent_1_size = 353; //353

const char* htmlContent_2 =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Input</title>"
"</head>"
"<body>"
"<h1>Send Data to ESP8266</h1>"
"<input type=\"text\" id=\"dataInput\" placeholder=\"Enter your data here\">"
"<button onclick=\"sendData()\">Send</button>"
"<script>"
"function sendData() {"
"const input = document.getElementById('dataInput').value;"
"fetch('/data', {"
"method: 'POST',"
"headers: {"
"'Content-Type': 'application/json',"
"},"
"body: JSON.stringify({ data: input }),"
"})"
".then(response => response.json())"
".then(data => {"
"console.log('Success:', data);"
"alert('Data sent successfully!');"
"})"
".catch((error) => {"
"console.error('Error:', error);"
"alert('Error sending data.');"
"});"
"}"
"</script>"
"</body>"
"</html>" ;
const size_t htmlContent_2_size = 734; // 734

const char* htmlContent_3 =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>Button Control</title>"
"<script>"
"function sendAction(action) {"
"fetch('/button_click', {"
"method: 'POST',"
"headers: {"
"'Content-Type': 'application/json'"
"},"
"body: JSON.stringify({ action: action })"
"})"
".then(response => response.json())"
".then(data => {"
"console.log(data); // Log the server response"
"})"
".catch(error => {"
"console.error('Error:', error);"
"});"
"}"
"</script>"
"</head>"
"<body>"
"<h1>Control Panel</h1>"
"<button onclick=\"sendAction('on')\">On</button>"
"<button onclick=\"sendAction('off')\">Off</button>"
"</body>"
"</html>";
const size_t htmlContent_3_size = 622; // 622

const char* htmlContent_4 =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Button Page</title>"
"<style>"
"body {"
"font-family: Arial, sans-serif;"
"text-align: center;"
"padding: 20px;"
"}"
".button {"
"font-size: 20px;"
"padding: 15px 30px;"
"margin: 20px;"
"cursor: pointer;"
"background-color: #4CAF50;"
"color: white;"
"border: none;"
"border-radius: 5px;"
"transition: background-color 0.3s;"
"}"
".button:hover {"
"background-color: #45a049;"
"}"
"</style>"
"</head>"
"<body>"
"<h1>Press a Button</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button 1 Pressed')\">Button 1</button>"
"<button class=\"button\" onclick=\"sendMessage('Button 2 Pressed')\">Button 2</button>"
"<script>"
"function sendMessage(message) {"
"fetch(`/send?message=${message}`)"
".then(response => console.log('Message sent:', message))"
".catch(error => console.error('Error sending message:', error));"
"}"
"</script>"
"</body>"
"</html>";
const size_t htmlContent_4_size = 885; // 885

// Send response back to client
const char* htmlContent_5 =
"HTTP/1.1 200 OK";
const size_t htmlContent_5_size = 15; // 15

web_page webpage_1(void)
{
	web_page page;
	page.str = (char*)htmlContent_1;
	page.size = htmlContent_1_size;
	return page;
}

web_page webpage_2(void)
{
	web_page page;
	page.str = (char*)htmlContent_2;
	page.size = htmlContent_2_size;
	return page;
}

web_page webpage_3(void)
{
	web_page page;
	page.str = (char*)htmlContent_3;
	page.size = htmlContent_3_size;
	return page;
}

web_page webpage_4(void)
{
	web_page page;
	page.str = (char*)htmlContent_4;
	page.size = htmlContent_4_size;
	return page;
}

web_page webpage_5(void)
{
	web_page page;
	page.str = (char*)htmlContent_5;
	page.size = htmlContent_5_size;
	return page;
}

/*** EOF ***/

/*** Comment ***
To calculate the size of the html file to use it in the at commands,
one should copy the text in a text editor, shift left the whole text,
then in the bottom it should indicate how many bytes it has, after that
subtract the number of lines to the number of characters to get the actual
size. To have a preview just change the file type to html and open it in
any internet explorer (chrome, firefox, etc).
If use it has a string has it is done here one must then escape all the special
characters, and add the parenthesis, for it used as a string.
****************/
