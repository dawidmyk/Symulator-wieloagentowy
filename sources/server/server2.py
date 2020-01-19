from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import cgi


#Klasa reprezentuje serwer HTTP
class Server(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def do_HEAD(self):
        self._set_headers()

    #metoda zwraca zadany plik
    def do_GET(self):
        self._set_headers()
        #usuwam '/' z nazwy pliku
        file_name = self.path.translate({ord('/'): None})
        with open(file_name, 'r') as file:
            message = file.read()

        self.wfile.write(message.encode())
        # self.wfile.write(json.dumps({'hello': 'world', 'received': 'ok'}).encode())


def run(server_class=HTTPServer, handler_class=Server, port=8008):
    server_address = ('localhost', 8081)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()


if __name__ == "__main__":
    run()