package osassign2;
//Mathew Vassair and Mihir Gupte
import java.net.*;
import java.io.*;

//The Echo Server for Assignment 2
//As far as I can tell, there's no input validation to do, since it's bytes in and bytes out.
//So unless a specific byte breaks Java somehow this should be totally safe
public class EchoServer {
	
	//EchoServer constructor, takes in port number as an int
	//Also runs the echo loop
	public EchoServer(int port){
		while(true){
		//Try with ServerSocket, Socket, and streams
			try ( ServerSocket servSock = new ServerSocket(port) ){
				  Thread sess = new Thread(new EchoSession(servSock.accept()));
				  sess.start();

			} catch (IOException e){
				System.out.println("Error while creating SessionThread");
				e.printStackTrace();
			}
		}
	}
	
	//Main method to run the server
	public static void main(String[] args) {
		int port = 0;
		try{
			port = Integer.parseInt(args[0]);
		} catch (NumberFormatException e){
			System.out.println("Usage: java EchoServer <port>");
		}
		new EchoServer(port);
	}
}
