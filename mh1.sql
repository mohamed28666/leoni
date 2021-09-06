-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1
-- Généré le : dim. 05 sep. 2021 à 00:55
-- Version du serveur : 10.4.20-MariaDB
-- Version de PHP : 7.3.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `leoni_lines`
--

-- --------------------------------------------------------

--
-- Structure de la table `mh1`
--

CREATE TABLE `mh1` (
  `LINE_NUMBER` text NOT NULL,
  `STATE` int(1) NOT NULL,
  `RT_RATIO` float NOT NULL,
  `START_TIME` datetime NOT NULL,
  `A_DURATION` time NOT NULL,
  `D_DURATION` time NOT NULL,
  `DISPLAY_LINE` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Déchargement des données de la table `mh1`
--

INSERT INTO `mh1` (`LINE_NUMBER`, `STATE`, `RT_RATIO`, `START_TIME`, `A_DURATION`, `D_DURATION`, `DISPLAY_LINE`) VALUES
('VW-L1', 0, 0, '2021-08-22 22:28:19', '44:28:19', '22:50:34', 1),
('VW-L2', 1, 10, '2021-08-30 00:10:07', '44:28:19', '65:50:34', 1),
('VW-L3', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1),
('VW-L4', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1),
('VW-L5', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1),
('VW-L6', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1),
('VW-L7', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1),
('VW-L8', 2, 66, '2021-08-30 00:10:54', '00:24:54', '47:10:54', 1);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `mh1`
--
ALTER TABLE `mh1`
  ADD PRIMARY KEY (`LINE_NUMBER`(200));
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
