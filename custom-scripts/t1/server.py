import time
import os
from http.server import BaseHTTPRequestHandler,HTTPServer
import psutil



HOST_NAME = '0.0.0.0' # !!!REMEMBER TO CHANGE THIS!!!
PORT_NUMBER = 8000

class MyHandler(BaseHTTPRequestHandler):
    def do_HEAD(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
    def do_GET(self):
        """Respond to a GET request."""
        datahora = os.popen('date').read()

        
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write("<html><head><title>Title goes here.</title></head>".encode())
        self.wfile.write("<body><p>This is a test.</p>".encode())
        self.wfile.write(f"<p>Data e Hora: {datahora}</p>".encode())

        self.get_uptime()
        self.modeloProcessador()
        self.capacidadeOcupadaProcessador()
        self.quantidadeMemoriaRam()
        self.versaoSistemaOperacional()
        self.listaProcessos()


        # If someone went to "http://something.somewhere.net/foo/bar/",
        # then self.path equals "/foo/bar/".
        self.wfile.write(f"<p>You accessed path: {self.path}</p>".encode())
        self.wfile.write("</body></html>".encode())

    def get_uptime(self):
        with open('/proc/uptime', 'r') as f:
            uptime_seconds = float(f.readline().split()[0])

        self.wfile.write(f"<p>Uptime: {uptime_seconds}</p>".encode())

    def modeloProcessador(self):
        # ● Modelo do processador e velocidade;
        
        modelo = os.popen('cat /proc/cpuinfo | grep "model name"').read()
        velocidade = os.popen('cat /proc/cpuinfo | grep "cpu MHz"').read()

        self.wfile.write(f"<p>Modelo CPU: <pre>{modelo}</pre></p>".encode())
        self.wfile.write(f"<p>Velocidade CPU:  <pre>{velocidade}</pre></p>".encode())

    def capacidadeOcupadaProcessador(self):
        # ● Capacidade ocupada do processador (%);
        
        cpu_percent = psutil.cpu_percent()
        self.wfile.write(f"<p>Capacidade ocupada do processador: {cpu_percent}%</p>".encode())


    def quantidadeMemoriaRam(self):
        # ● Quantidade de memória RAM total e usada (MB);
        mem = os.popen('free -m | grep Mem').read()
        total = mem.split()[1]
        used = mem.split()[2]

        self.wfile.write(f"<p>Memória total: {total}MB</p>".encode())
        self.wfile.write(f"<p>Memória usada: {used}MB</p>".encode())

    def versaoSistemaOperacional(self):
        version = os.popen('uname -a').read()
        self.wfile.write(f"<p>Versão do SO: {version}</p>".encode())

    def listaProcessos(self):
        # Lista de processos em execução (pid e nome)
        processos = os.popen('ps -A -o "pid,comm"').read()
        self.wfile.write(f"<p>Processos: <pre>{processos}</pre></p>".encode())

if __name__ == '__main__':
    httpd = HTTPServer((HOST_NAME, PORT_NUMBER), MyHandler)
    print("Server Starts - %s:%s" % (HOST_NAME, PORT_NUMBER))
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print("Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER))
