package model.dao;

import connection.ConnectionFactory;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import model.bean.Tempo;

/**
 *
 * @author pedro
 */
public class TempoDAO {
    
    public boolean save (Tempo temp) {
        
        Connection con = ConnectionFactory.getConnection();
        PreparedStatement stmt = null;
        
        try {
            stmt = con.prepareStatement("INSERT INTO Tempos (volta,tempo1,tempo2,tempo3) VALUES(?,?,?,?)");
            stmt.setInt(1, temp.getVoltas());
            stmt.setString(2, temp.getValorTemp1());
            stmt.setString(3, temp.getValorTemp2());
            stmt.setString(4, temp.getValorTemp3());
            
            stmt.executeUpdate();
            
            return true;
            
        } catch (SQLException ex) {
            //System.err.println("Erro ao salvar: "+ex);
            
            return false;
        } finally {
            ConnectionFactory.closeConnection(con, stmt);
        }
    }
}


