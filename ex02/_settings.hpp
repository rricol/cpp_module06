/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _settings.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rricol <rricol@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:16:41 by rricol            #+#    #+#             */
/*   Updated: 2023/02/02 09:00:36 by rricol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// includes library
#include <iostream>
#include <ostream> // pour la manipulation de l'output
#include <fstream> // pour la création de fichier
#include <exception> // pour les exceptions
#include <limits>

// includes hpp files
#include "Base.hpp"

// Defines
#define BOLD_BLACK	"\033[1m\033[30m"
#define BOLD_RED	"\033[1m\033[31m"
#define BOLD_G		"\033[1m\033[32m"
#define BOLD_C		"\033[1m\033[36m"
#define BOLD_B		"\033[1m\033[34m"
#define BOLD_P		"\033[1m\033[35m"
#define RESET		"\033[0m"
#define BOLD_Y		"\033[1m\033[33m"
#define BOLD_W		"\033[1m\033[37m"
#define LOG			BOLD_BLACK << "[-] " << RESET
#define SUCCESS		BOLD_G << "[✓] " << RESET
#define INFO		BOLD_B << "[ℹ] " << RESET
#define ERROR		BOLD_RED << "[×] " << RESET
#define WARNING		BOLD_Y << "[!] " << RESET
#define DECO		BOLD_C << "✱ " << RESET

// Class prototypes

class Base;
