#include "help_command.h"

namespace CodEXpander::Core {
    void HelpCommand::Execute() {
        auto displayTextColor = Color::White();

        logger.PrintLineInfoMessage("");
        logger.PrintMessage("Usage:", displayTextColor);
        logger.PrintLineInfoMessage("     codexpander [OPTIONS]");
        logger.PrintLineInfoMessage("");
        logger.PrintLineMessage("Description:", displayTextColor);
        logger.PrintLineInfoMessage("A tool to resolve header include statements in a source file and enlist the content based on the correct call and structure hierarchy.");
        logger.PrintLineInfoMessage("");
        logger.PrintLineMessage("Options:", displayTextColor);
        logger.PrintMessage("   --source_file       ", displayTextColor);
        logger.PrintLineInfoMessage("Specifies the source file to be expanded");
        logger.PrintMessage("   --output_file       ", displayTextColor);
        logger.PrintLineInfoMessage("Specifies the expanded source file to be created by a given valid path");
        logger.PrintMessage("   --working_dir       ", displayTextColor);
        logger.PrintLineInfoMessage("Specifies the root directory where the include directory should exist to look for header files");
        logger.PrintLineMessage("", displayTextColor);
    }
}