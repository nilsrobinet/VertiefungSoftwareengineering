"""Main module of the demo application showcasing the python compatible library
for using the Eigenface algorithm"""
import os
import sys
import cherrypy # pylint: disable=E0401

from .eigenfaceDispatcher import EigenfaceDispatcher

class EigenfaceDemo:
    """Object for configuring and managing a cherrypy web server"""
    def __init__(self):
        pass

    def configure(self):
        """Configure the webapp"""
        # Get current directory
        try:
            currentDir = os.path.dirname(os.path.abspath(__file__))
        except OSError:
            currentDir = os.path.dirname(os.path.abspath(sys.executable))
        # disable autoreload
        cherrypy.engine.autoreload.unsubscribe()
        cherrypy.server.socket_host = '0.0.0.0'
        # Static content config
        staticConfig= {
           '/': {
               'tools.staticdir.root': currentDir,
               'tools.staticdir.on': True,
               'tools.staticdir.dir': '../content',
               'tools.staticdir.index': 'index.html'
            }
        }
        # Mount static content handler
        cherrypy.tree.mount(None, '/', staticConfig)
        # Mount eingefaceApi
        cherrypy.tree.mount(EigenfaceDispatcher(), '/api/eigenfaces')
        # suppress traceback-info
        cherrypy.config.update({'request.show_tracebacks': False})

    def run(self):
        """Start the webserver"""
        # Start server
        cherrypy.engine.start()
        cherrypy.engine.block()
