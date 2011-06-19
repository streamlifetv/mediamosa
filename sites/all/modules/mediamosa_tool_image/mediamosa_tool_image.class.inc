<?php
// $Id$

/**
 * MediaMosa is Open Source Software to build a Full Featured, Webservice
 * Oriented Media Management and Distribution platform (http://mediamosa.org)
 *
 * Copyright (C) 2011 SURFnet BV (http://www.surfnet.nl) and Kennisnet
 * (http://www.kennisnet.nl)
 *
 * MediaMosa is based on the open source Drupal platform and
 * was originally developed by Madcap BV (http://www.madcap.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, you can find it at:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

/**
 * @file
 * Image tool functions.
 */
class mediamosa_tool_image {
  /**
   * Mime type: image/tiff
   */
  const MEDIAMOSA_TOOL_IMAGE_MIME_TYPE_TIFF = 'image/tiff';

  /**
   * Name / ID of the module.
   */
  const NAME = 'image';

  /**
   * Key value separator.
   */
  const MEDIAMOSA_TOOL_IMAGE_KEY_VALUE_SEPARATOR = ':';

  /**
   * Warning level for ImageMagic.
   */
  const MEDIAMOSA_MAINTENANCE_STATUS_CONFIGURATION_IMAGEMAGIC_WARNING = '6';

  /**
   * Returns TRUE when we support this mime-type.
   *
   * @param string $mime_type
   */
  static public function is_supported($mime_type) {
    return preg_match('#^image\/.+#', $mime_type);
  }

  /**
   * Generate still.
   *
   * @deprecated: Although new, its deprecated. We will replace this function
   *              with generate_still() very soon and no longer rely on exec
   *              strings return. Rewrite of jobs is planned for v3.5.
   *
   * @param string $jobserver_job_id
   * @param string $mediafile_id_source
   */
  static public function get_generate_still_exec($jobserver_job_id, $mediafile_id_source) {

    $job_server_still = mediamosa_job_server_still::get($jobserver_job_id);
    $job_server = mediamosa_job_server::get($jobserver_job_id);
    $job_id = $job_server[mediamosa_job_server_db::JOB_ID];

    $execution_string = '';

    if ($job_server_still) {
      $size = $job_server_still[mediamosa_job_server_still_db::SIZE]; // wxh
      $h_padding = $job_server_still[mediamosa_job_server_still_db::H_PADDING];
      $v_padding = $job_server_still[mediamosa_job_server_still_db::V_PADDING];

      // Get width and height.
      list($width, $height) = explode('x', $size, 2);

      // Dest.
      // mediamosa_configuration_storage::mount_point_get() . DIRECTORY_SEPARATOR . mediamosa_configuration_storage::data_location_get()
    }

    return '';
/*
    // Build the values.
    $execution_string_options = array(
      '@file_location' => dirname($options['location_dest_file']) . DIRECTORY_SEPARATOR . $options['jobserver_job_id'] . DIRECTORY_SEPARATOR,
      '@mediafile_location' => $options['location_source_file'],
      '@mediafile_id' => $options['mediafile_id'],
      '@params' => $options['parameter_string'],
    );

    // Execution string.
    // Go to the subdirectory.
    // Create jpg from image (eg. from tiff).
    // Copy the result to transcode directory.
    // Remove the temporary directory (and files).
    // Create status file.
    return strtr('mkdir @file_location; cd @file_location; convert @mediafile_location @params @mediafile_id.jpg; cp @mediafile_id.jpg ../@mediafile_id.jpg; cd ..; rm @file_location -r; { echo "Errors: none"; echo "Status: done"; echo "Progress: 1.000"; echo "Warnings: none"; } > @mediafile_id.status;', $options);
*/
  }

  /**
   * Get the exec string for transcoding the file.
   *
   * @deprecated: Although new, its deprecated. We will replace this function
   *              with transcode() very soon and no longer rely on exec
   *              strings return. Rewrite of jobs is planned for v3.5.
   *
   * @param array $options
   */
  static public function get_transcode_exec($options) {

    // Build the values.
    $execution_string_options = array(
      '@file_location' => dirname($options['location_dest_file']) . DIRECTORY_SEPARATOR . $options['jobserver_job_id'] . DIRECTORY_SEPARATOR,
      '@mediafile_location' => $options['location_source_file'],
      '@mediafile_id' => $options['mediafile_id'],
      '@parameter_string' => $options['parameter_string'],
    );

    // Execution string.
    // Go to the subdirectory.
    // Create jpg from image (eg. from tiff).
    // Copy the result to transcode directory.
    // Remove the temporary directory (and files).
    // Create status file.
    return strtr('mkdir @file_location; cd @file_location; convert @mediafile_location @parameter_string @mediafile_id.jpg; cp @mediafile_id.jpg ../@mediafile_id.jpg; cd ..; rm @file_location -r; { echo "Errors: none"; echo "Status: done"; echo "Progress: 1.000"; echo "Warnings: none"; } > @mediafile_id.status;', $options);
  }
}