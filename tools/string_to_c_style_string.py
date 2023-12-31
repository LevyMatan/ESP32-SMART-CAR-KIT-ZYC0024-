"""
string_to_c_style_string.py

"""
def html_to_c_string(html_string):
    """
    Convert a string to a C-style string
    """
    # Escape double quotes and backslashes
    html_string = html_string.replace('\\', '\\\\')
    html_string = html_string.replace('"', '\\"')

    # Add quotes around the string and terminate with a null character
    c_string = '"' + html_string + '\\0"'

    return c_string

if __name__ == '__main__':
    
    STRING = """<!DOCTYPE HTML><html><head><title>Joy</title><meta charset="utf-8"><meta name="description" content="ESP32 Remote Controller for Car"><meta name="author" content="Matan Levy"><script src="https:</head><body> <div id="joyDiv-turn" style="width:200px;height:200px;margin-bottom:20px;"></div> <div id="joyDiv-speed" style="width:200px;height:200px;margin-bottom:20px;"></div> <p id="speed-value">Speed Value: </p> <p id="turn-value">Turn Value: </p> <script type="text/javascript"> var speed = 0; var turn = 0; function sendGetWithParams(speed_arg, turn_arg) { var xhttp = new XMLHttpRequest(); var arg = speed_arg + "," + turn_arg; xhttp.open('GET', 'move' + '?' + arg, true); xhttp.send() } function updateHtmlInfo(speed_arg, turn_arg) { document.getElementById("speed-value").innerHTML = "Speed Value: " + speed_arg; document.getElementById("turn-value").innerHTML = "Turn Value: " + turn_arg; } var JoyTurn = new JoyStick('joyDiv-turn', {}, function(stickData) { turn = stickData.x; updateHtmlInfo(speed, turn); sendGetWithParams(speed, turn); }); var JoySpeed = new JoyStick('joyDiv-speed', {}, function(stickData) { speed = stickData.y; updateHtmlInfo(speed, turn); sendGetWithParams(speed, turn); }); </script> </body></html>"""
    C_STRING = html_to_c_string(STRING)

    print('C-style string:')
    print(C_STRING)
