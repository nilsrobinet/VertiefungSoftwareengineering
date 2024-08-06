"""This module contains the class that implements the method dispatcher for the webapp"""
import cherrypy # pylint: disable=E0401

@cherrypy.expose
class EigenfaceDispatcher:
    """Dispatcher object exposing the eigenface functions to the HTTP web interface"""
    def __init__(self) -> None:
        pass

    def generateEigenfaces(self):
        """TODO: implement"""

    def getSimilarFace(self):
        """TODO: implement"""
