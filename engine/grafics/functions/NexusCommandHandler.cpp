#include "NexusCommandHandler.h"
#include "nexusConsole.h"

NexusCommandHandler::NexusCommandHandler() {
    commands["say"] = [this](const std::vector<std::string>& args) {
        if (args.empty()) return;

        // 1. Собираем сообщение из аргументов
        std::string message;
        for (const auto& arg : args) message += arg + " ";

        // 2. Формируем финальную строку для отправки
        std::string payload = "[Nexus]: " + message;

        // 3. Выводим локально в ImGui (чтобы ты сам видел, что написал)
        // ВАЖНО: Нам нужен доступ к консоли. 
        // Мы чуть подправим вызов ниже, чтобы это работало.
    };
    commands["exit"] = [](const std::vector<std::string>& args) {
        exit(0);
    };




}

void NexusCommandHandler::Draw(GLFWwindow* window, NexusConsole& console) {
    ImGui::Begin("Nexus System Console");

    // 1. Логи
    float footer_height = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height), true);
    for (auto it = console.begin(); it != console.end(); ++it) {
        ImGui::TextUnformatted(it->c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();

    ImGui::Separator();

    // 2. Ввод
    if (ImGui::InputText("##cmd", console.InputBuf, 256, ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string cmd(console.InputBuf);
        if (!cmd.empty()) {
            console.AddLog("> " + cmd);
            this->Process(cmd, console); // Вызываем обработку команд
        }
        console.InputBuf[0] = '\0';
        ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::End();
}





void NexusCommandHandler::Process(const std::string& input, NexusConsole& console) {
    std::vector<std::string> tokens = split(input);
    if (tokens.empty()) return;

    std::string cmdName = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    if (commands.count(cmdName)) {
        // --- ВОТ ТУТ МАГИЯ ---
        // Если это команда 'say', обрабатываем её с доступом к сокету
        if (cmdName == "say") {
            std::string message;
            for (const auto& arg : args) message += arg + " ";
            
            // Отправка в ZMQ (если сокет подключен)
            if (console.NetworkSocket) {
                std::string payload = "[Nexus]: " + message;
                console.NetworkSocket->send(zmq::buffer(payload), zmq::send_flags::none);
            }
            
            // Вывод в локальный лог ImGui
            console.AddLog("[You]: " + message);
        } 
        else {
            commands[cmdName](args); // Остальные команды (help, clear и т.д.)
        }
    } else {
        console.AddLog("[Error]: Unknown command " + cmdName);
    }
}

std::vector<std::string> NexusCommandHandler::split(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string t;
    while (iss >> t) tokens.push_back(t);
    return tokens;
}


