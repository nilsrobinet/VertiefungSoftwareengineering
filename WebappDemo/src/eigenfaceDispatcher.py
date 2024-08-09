"""This module contains the class that implements the method dispatcher for the webapp"""
import os
import cherrypy # pylint: disable=E0401

class EigenfaceDispatcher:
    """Dispatcher object exposing the eigenface functions to the HTTP web interface"""
    def __init__(self) -> None:
        pass

    @cherrypy.expose
    def generateEigenfaces(self):
        """TODO: implement"""

    @cherrypy.expose
    def getSimilarFace(self):
        """TODO: implement"""
