"""
html_to_c_variable.py

Description: Converts an HTML file to a C-style variable with string
"""
import html_comprresser
import string_to_c_style_string

def html_to_c_variable(html_file_path, variable_name):
    """
    Converts an HTML file to a C-style variable with string

    Args:
        html_file_path (str): The path to the HTML file to convert.
        variable_name (str): The name of the variable.

    Returns:
        str: The C-style variable as a string.
    """
    #compress the HTML file
    compressed_html = html_comprresser.compress_html_file(html_file_path)

    # Convert the HTML to a C-style string
    c_string = string_to_c_style_string.html_to_c_string(compressed_html)

    # Add variable name
    c_variable = 'extern String ' + variable_name + ' = ' + c_string + ';'

    return c_variable

if __name__ == '__main__':
    import sys

    INPUT_HTML_FILE_PATH = """../src/webserver/joysticks.html"""
    HTML_FILE_PATH = """../src/webserver/html_string.cpp"""
    VARIABLE_NAME = "page"
    C_VARIABLE = html_to_c_variable(INPUT_HTML_FILE_PATH, VARIABLE_NAME)

    with open(HTML_FILE_PATH, 'w', encoding='utf-8') as file:
        file.write('/* This file was automatically generated by html_to_c_variable.py */\n')
        file.write('#include <Arduino.h>\n\n')
        file.write(C_VARIABLE)
