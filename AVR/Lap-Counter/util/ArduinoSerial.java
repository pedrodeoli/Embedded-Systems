package util;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.TooManyListenersException;


public class ArduinoSerial implements SerialPortEventListener {

    private SerialPort serialPort;
    private final String namePort;
    
    private String minTrecho1;
    private String segTrecho1;
    private String milTrecho1;
    private String minTrecho2;
    private String segTrecho2;
    private String milTrecho2;
    private String minTrecho3;
    private String segTrecho3;
    private String milTrecho3;
    private String voltas;

    private String leituraComando;
    
    public ArduinoSerial(String portName) {
        this.namePort = portName;
    }

    /**
     * A BufferedReader which will be fed by a InputStreamReader converting the
     * bytes into characters making the displayed results codepage independent
     */
    private BufferedReader input;
    /**
     * The output stream to the port
     */
    private OutputStream output;
    /**
     * Milliseconds to block while waiting for port open
     */
    private static final int TIME_OUT = 2000;
    /**
     * Default bits per second for COM port.
     */
    private static final int DATA_RATE = 9600;

    private String inputLine;

    public void initialize() {
        CommPortIdentifier portId = null;
        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

        //First, Find an instance of serial port as set in PORT_NAMES.
        while (portEnum.hasMoreElements()) {
            CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
            if (namePort.equals(currPortId.getName())) {
                portId = currPortId;
                break;
            }
        }
        if (portId == null) {
            System.out.println("Could not find COM port.");
            return;
        }

        try {
            // open serial port, and use class name for the appName.
            serialPort = (SerialPort) portId.open(this.getClass().getName(),
                    TIME_OUT);

            // set port parameters
            serialPort.setSerialPortParams(DATA_RATE,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);

            // open the streams
            input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
            output = serialPort.getOutputStream();

            // add event listeners
            serialPort.addEventListener(this);
            serialPort.notifyOnDataAvailable(true);
        } catch (PortInUseException | UnsupportedCommOperationException | IOException | TooManyListenersException e) {
            System.err.println(e.toString());
        }
    }

    public void send(String data) {
        try {
            output.write(data.getBytes());
        } catch (Exception e) {
            System.err.println(e.toString());
        }
    }

    public String read() {
        return inputLine;
    }

    public void sleep(int time) {
        try {
            Thread.sleep(time);
        } catch (InterruptedException e) {
            System.err.println(e.toString());
        }
    }

    /**
     * This should be called when you stop using the port. This will prevent
     * port locking on platforms like Linux.
     */
    public synchronized void close() {
        if (serialPort != null) {
            serialPort.removeEventListener();
            serialPort.close();
        }
    }

    /**
     * Handle an event on the serial port. Read the data and print it.
     *
     * @param oEvent
     */
    @Override
    public synchronized void serialEvent(SerialPortEvent oEvent) {
        if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
            try {
                inputLine = input.readLine();
                this.setLeituraComando(inputLine);
                
            } catch (Exception e) {
                System.err.println(e.toString());
            }
        }
        // Ignore all the other eventTypes, but you should consider the other ones.
    }
    
       private void interpretaComando(){
        String aux[] = leituraComando.split(";"); 
        minTrecho1 = aux[0];
        segTrecho1 = aux[1];
        milTrecho1 = aux[2];
        minTrecho2 = aux[3];
        segTrecho2 = aux[4];
        milTrecho2 = aux[5];
        minTrecho3 = aux[6];
        segTrecho3 = aux[7];
        milTrecho3 = aux[8];
        voltas = aux[9];
       
        }


    public String getLeituraComando() {
        return leituraComando;
    }

    public void setLeituraComando(String leituraComando) {
        this.leituraComando = leituraComando;
        this.interpretaComando();
    }

    public String getMinTrecho1() {
        return minTrecho1;
    }

    public void setMinTrecho1(String minTrecho1) {
        this.minTrecho1 = minTrecho1;
    }

    public String getSegTrecho1() {
        return segTrecho1;
    }

    public void setSegTrecho1(String segTrecho1) {
        this.segTrecho1 = segTrecho1;
    }

    public String getMilTrecho1() {
        return milTrecho1;
    }

    public void setMilTrecho1(String milTrecho1) {
        this.milTrecho1 = milTrecho1;
    }

    public String getMinTrecho2() {
        return minTrecho2;
    }

    public void setMinTrecho2(String minTrecho2) {
        this.minTrecho2 = minTrecho2;
    }

    public String getSegTrecho2() {
        return segTrecho2;
    }

    public void setSegTrecho2(String segTrecho2) {
        this.segTrecho2 = segTrecho2;
    }

    public String getMilTrecho2() {
        return milTrecho2;
    }

    public void setMilTrecho2(String milTrecho2) {
        this.milTrecho2 = milTrecho2;
    }

    public String getMinTrecho3() {
        return minTrecho3;
    }

    public void setMinTrecho3(String minTrecho3) {
        this.minTrecho3 = minTrecho3;
    }

    public String getSegTrecho3() {
        return segTrecho3;
    }

    public void setSegTrecho3(String segTrecho3) {
        this.segTrecho3 = segTrecho3;
    }

    public String getMilTrecho3() {
        return milTrecho3;
    }

    public void setMilTrecho3(String milTrecho3) {
        this.milTrecho3 = milTrecho3;
    }

    public String getVoltas() {
        return voltas;
    }

    public void setVoltas(String voltas) {
        this.voltas = voltas;
    }

}
