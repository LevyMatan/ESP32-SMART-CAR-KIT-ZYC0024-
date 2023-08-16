"""
html_comprresser.py

Description: Compresses HTML files by removing all whitespace and comments
"""
import re

def compress_html_file(file_path):
    """
    Compresses an HTML file by removing all whitespace and comments.

    Args:
        file_path (str): The path to the HTML file to compress.

    Returns:
        str: The compressed HTML as a string.
    """
    with open(file_path, 'r', encoding='utf-8') as file:
        html = file.read()

    # Remove comments
    html = re.sub(r'<!--.*?-->', '', html, flags=re.DOTALL)

    # Remove C-style comments
    html = re.sub(r'//.*?\n|/\*.*?\*/', '', html, flags=re.DOTALL)

    # Restore URLs
    html = re.sub(r'(?P<url>https?://[^\s]+)', r'<\g<url>>', html)

    # Remove line breaks
    html = html.replace('\n', '')

    # Remove tab spaces
    html = html.replace('\t', '')

    # Replace multiple spaces with a single space
    html = ' '.join(html.split())

    return html

if __name__ == '__main__':
    import sys

    if len(sys.argv) < 2:
        print('Usage: python html_compressor.py <html_file>')
        sys.exit(1)

    HTML_FILE_PATH = sys.argv[1]
    compressed_html = compress_html_file(HTML_FILE_PATH)

    print('Compressed HTML:')
    print(compressed_html)
