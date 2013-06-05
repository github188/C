// MessageParserFactory.h
#ifndef __MESSAGEPARSERFACTORY_H__
#define __MESSAGEPARSERFACTORY_H__

/*
import org.jscsi.parser.data.DataInParser;
import org.jscsi.parser.data.DataOutParser;
import org.jscsi.parser.login.LoginRequestParser;
import org.jscsi.parser.login.LoginResponseParser;
import org.jscsi.parser.logout.LogoutRequestParser;
import org.jscsi.parser.logout.LogoutResponseParser;
import org.jscsi.parser.nop.NOPInParser;
import org.jscsi.parser.nop.NOPOutParser;
import org.jscsi.parser.r2t.Ready2TransferParser;
import org.jscsi.parser.reject.RejectParser;
import org.jscsi.parser.scsi.SCSICommandParser;
import org.jscsi.parser.scsi.SCSIResponseParser;
import org.jscsi.parser.snack.SNACKRequestParser;
import org.jscsi.parser.text.TextRequestParser;
import org.jscsi.parser.text.TextResponseParser;
import org.jscsi.parser.tmf.TaskManagementFunctionRequestParser;
import org.jscsi.parser.tmf.TaskManagementFunctionResponseParser;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
*/
/**
* MessageParserFactory
* This class creates a specified parser object. But only one object of this kind. 
* With this technique it minimizes the object creation process and affect the 
* execution speed, too.
*/
class MessageParserFactory {
public:
    /** Default constructor, which prevent a instance of this class. */
    MessageParserFactory();
    ~MessageParserFactory();

public:
	/**
	 * Returns the parser object with the given operation code.
	 *
	 * @param protocolDataUnit
	 * The reference ProtocolDataUnit instance, which
	 * contains this AbstractMessageParser object.
	 * @param operationCode
	 * The operation code of the requested AbstractMessageParser.
	 * @return The instance of the requested AbstractMessageParser.
	 * @see org.jscsi.parser.OperationCode
	 */
    static AbstractMessageParser getParser(ProtocolDataUnit protocolDataUnit,
        OperationCode operationCode);

private:
	/**
	 * Creates an instance of a concrete AbstractMessageParser object.
	 *
	 * @param protocolDataUnit
	 * The reference ProtocolDataUnit instance, which
	 * contains this AbstractMessageParser object.
	 * @param operationCode
	 * The operation code of the requested AbstractMessageParser.
	 * @return The instance of the requested AbstractMessageParser.
	 * @see org.jscsi.parser.OperationCode
	 */
    static AbstractMessageParser createParser(ProtocolDataUnit protocolDataUnit,
        OperationCode operationCode);
};

#endif // __MESSAGEPARSERFACTORY_H__
