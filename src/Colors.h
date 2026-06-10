#pragma once
#include "string"

const std::string RESET     {"\033[0m" };
const std::string BOLD      { "\033[1m" };
const std::string CYAN      { "\033[1;36m" };
const std::string YELLOW    { "\033[1;33m" };
const std::string GRAY      { "\033[90m" };
const std::string BG_BGREEN { "\033[48;5;22m" };    // Темно-зеленый фон
const std::string BG_BRED   {"\033[48;5;52m"};      // Темно-красный фон
const std::string FG_WHITE  { "\033[97m" };         // Яркий белый текст
const std::string FG_GOLD   { "\033[38;5;220m" };   // Золотой текст для счета