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


const char* htmlContent_5 =
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
".button:disabled {"
"background-color: #ccc;"
"cursor: not-allowed;"
"}"
".button:hover {"
"background-color: #45a049;"
"}"
"</style>"
"</head>"
"<body>"
"<h1>Press a Button</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button 1 Pressed')\" id=\"button1\">Button 1</button>"
"<button class=\"button\" onclick=\"sendMessage('Button 2 Pressed')\" id=\"button2\">Button 2</button>"
"<script>"
"function sendMessage(message) {"
"// Disable both buttons to prevent multiple clicks"
"document.getElementById('button1').disabled = true;"
"document.getElementById('button2').disabled = true;"
"fetch(`/send?message=${message}`)"
".then(response => {"
"console.log('Message sent:', message);"
"// Re-enable buttons after successful response"
"document.getElementById('button1').disabled = false;"
"document.getElementById('button2').disabled = false;"
"})"
".catch(error => {"
"console.error('Error sending message:', error);"
"// Re-enable buttons even if there is an error"
"document.getElementById('button1').disabled = false;"
"document.getElementById('button2').disabled = false;"
"});"
"}"
"</script>"
"</body>"
"</html>";
const size_t htmlContent_5_size = 1335; // 1335

const char* htmlContent_6 =
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
".button:disabled {"
"background-color: #ccc;"
"cursor: not-allowed;"
"}"
".button:hover:not(:disabled) {"
"background-color: #45a049;"
"}"
"</style>"
"</head>"
"<body>"
"<h1>Press a Button</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button 1 Pressed', 'button1')\" id=\"button1\">Button 1</button>"
"<button class=\"button\" onclick=\"sendMessage('Button 2 Pressed', 'button2')\" id=\"button2\">Button 2</button>"
"<script>"
"function sendMessage(message, buttonId) {"
"const button = document.getElementById(buttonId);"
"button.disabled = true;"
"fetch(`/send?message=${encodeURIComponent(message)}`)"
".then(response => {"
"if (response.ok) {"
"console.log(\"Message sent:\", message);"
"} else {"
"console.error(\"Server error:\", response.status);"
"}"
"button.disabled = false;"
"})"
".catch(error => {"
"console.error(\"Network error:\", error);"
"button.disabled = false;"
"});"
"}"
"</script>"
"</body>"
"</html>";
const size_t htmlContent_6_size = 1233; // 1233

const char* htmlContent_7 =
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
".button:disabled {"
"background-color: #ccc;"
"cursor: not-allowed;"
"}"
".button:hover:not(:disabled) {"
"background-color: #45a049;"
"}"
"</style>"
"</head>"
"<body>"
"<h1>Press a Button</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button 1 Pressed', 'button1')\" id=\"button1\">Button 1</button>"
"<button class=\"button\" onclick=\"sendMessage('Button 2 Pressed', 'button2')\" id=\"button2\">Button 2</button>"
"<script>"
"let requestInProgress = false;"
"function sendMessage(message, buttonId) {"
"if (requestInProgress) {"
"console.log(\"Request in progress, ignoring button press:\", message);"
"return;"
"}"
"requestInProgress = true;"
"const button = document.getElementById(buttonId);"
"button.disabled = true;"
"fetch(`/send?message=${encodeURIComponent(message)}`)"
".then(response => {"
"if (response.ok) {"
"console.log(\"Message sent:\", message);"
"} else {"
"console.error(\"Server error:\", response.status);"
"}"
"button.disabled = false;"
"requestInProgress = false;"
"})"
".catch(error => {"
"console.error(\"Network error:\", error);"
"button.disabled = false;"
"requestInProgress = false;"
"});"
"}"
"</script>"
"</body>"
"</html>";
const size_t htmlContent_7_size = 1441; // 1441

// Send response back to client
const char* htmlContent_200 =
"HTTP/1.1 200 OK";
const size_t htmlContent_200_size = 15; // 15

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

web_page webpage_6(void)
{
	web_page page;
	page.str = (char*)htmlContent_6;
	page.size = htmlContent_6_size;
	return page;
}

web_page webpage_7(void)
{
	web_page page;
	page.str = (char*)htmlContent_7;
	page.size = htmlContent_7_size;
	return page;
}

web_page webpage_200(void)
{
	web_page page;
	page.str = (char*)htmlContent_200;
	page.size = htmlContent_200_size;
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
